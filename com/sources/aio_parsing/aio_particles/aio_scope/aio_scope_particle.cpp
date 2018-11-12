//native:
#include <typeinfo>
//lang:
#include <aio_lang/aio_space/aio_space.h>
#include <aio_lang/aio_modifiers/aio_modifiers.h>
#include <aio_lang/aio_space/aio_scope/aio_scope.h>
//parsing:
#include <aio_parsing/aio_particles/aio_scope/aio_scope_particle.h>
//lib4aio:
#include <lib4aio_cpp_headers/aio_explorer/aio_explorer.h>
#include <lib4aio_cpp_headers/utils/char_utils/char_utils.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

#define AIO_SCOPE_PARTICLE_INFO_TAG "AIO_SCOPE_MODIFIER_INFO"

#define AIO_SCOPE_PARTICLE_ERROR_TAG "AIO_SCOPE_MODIFIER_ERROR"

#define AIO_SCOPE_PARTICLE_DEBUG

aio_scope_particle::aio_scope_particle()
{}

aio_scope_particle::~aio_scope_particle()
{}

const aio_particle_signal aio_scope_particle::handle_symbol(const unsigned position)
{
    const char symbol = this->radius_ptr->get_string()[position];
    switch (this->monitor_mode) {
        case AIO_MONITOR_MODIFIER:
            this->monitor_scope_modifier(symbol, position);
            break;
        case AIO_MONITOR_NAME:
            this->monitor_scope_name(symbol, position);
            break;
        case AIO_MONITOR_KEY:
            this->monitor_scope_key(symbol, position);
            break;
        case AIO_MONITOR_ATTRIBUTES:
            this->monitor_scope_attributes(symbol, position);
            break;
        case AIO_MONITOR_BODY:
            this->monitor_scope_body(symbol, position);
            break;
    }
    return this->signal;
}

void aio_scope_particle::monitor_scope_modifier(const char symbol, const unsigned position)
{
    //기호를 확인하다:
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    //Start:
    const bool is_token_scan_started = !is_whitespace_cond && this->trigger_mode == AIO_TRIGGER_MODE_PASSIVE;
    if (is_token_scan_started) {
        this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
        this->token_holder->start = position;
    }
    const bool is_token_scan_finished = is_whitespace_cond && this->trigger_mode == AIO_TRIGGER_MODE_ACTIVE;
    if (is_token_scan_finished) {
        this->token_holder->end = position;
        const bool is_scope_modifier = is_aio_scope_modifier(this->token_holder);
        if (is_scope_modifier) {
#ifdef AIO_SCOPE_PARTICLE_DEBUG
            log_info_str_hook(AIO_SCOPE_PARTICLE_INFO_TAG, "Found modifier:", this->token_holder);
#endif
            this->scope_ptr = new aio_scope();
            //Prepare to the next state:
            this->monitor_mode = AIO_MONITOR_NAME;
            this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
            this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
        }
    }
}

void aio_scope_particle::monitor_scope_name(const char symbol, const unsigned position)
{
    //기호를 확인하다:
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    //Start:
    const bool is_token_scan_started = !is_whitespace_cond && this->trigger_mode == AIO_TRIGGER_MODE_PASSIVE;
    if (is_token_scan_started) {
        this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
        this->token_holder->start = position;
        return;
    }
    const bool is_semicolon_cond = is_semicolon(symbol);
    const bool is_colon_cond = is_colon(symbol);
    const bool is_token_scan_finished = (is_whitespace_cond || is_semicolon_cond || is_colon_cond)
                                        && this->trigger_mode == AIO_TRIGGER_MODE_ACTIVE;
    if (is_token_scan_finished) {
        this->token_holder->end = position;
        const bool is_valid_scope_name = this->token_holder->is_word();
//                && !this->scope_list_ptr->contains_by(
//                [this](aio_scope *it) -> bool {
//                    return it->name->equals_string(this->token_holder);
//                });
        if (is_valid_scope_name) {
#ifdef AIO_SCOPE_PARTICLE_DEBUG
            log_info_str_hook(AIO_SCOPE_PARTICLE_INFO_TAG, "Found name:", this->token_holder);
#endif
            this->scope_ptr->name = new str_hook(this->token_holder);
            this->switch_monitor_mode(symbol, position);
            this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
        }
    }
}

void aio_scope_particle::monitor_scope_key(const char symbol, const unsigned position)
{
    const bool is_whitespace = is_space_or_line_break(symbol);
    if (!is_whitespace) {
        this->switch_monitor_mode(symbol, position);
    }
}

void aio_scope_particle::monitor_scope_attributes(const char symbol, const unsigned position)
{
    //기호를 확인하다:
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    //Start:
    const bool is_token_scan_started = !is_whitespace_cond && this->trigger_mode == AIO_TRIGGER_MODE_PASSIVE;
    if (is_token_scan_started) {
        this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
        this->token_holder->start = position;
        return;
    }
    const bool is_semicolon_cond = is_semicolon(symbol);
    const bool is_colon_cond = is_colon(symbol);
    const bool is_token_scan_finished = (is_whitespace_cond || is_semicolon_cond || is_colon_cond)
                                        && this->trigger_mode == AIO_TRIGGER_MODE_ACTIVE;
    if (is_token_scan_finished) {
        this->token_holder->end = position;
        const bool is_protected_modifier_cond = is_aio_protected_modifier(this->token_holder);
        const bool is_private_modifier_cond = is_aio_private_modifier(this->token_holder);
        const bool is_attribute_keyword = is_protected_modifier_cond || is_private_modifier_cond;
        if (is_attribute_keyword) {
#ifdef AIO_SCOPE_PARTICLE_DEBUG
            log_info_str_hook(AIO_SCOPE_PARTICLE_INFO_TAG, "Found attribute:", this->token_holder);
#endif
//            if (is_private_modifier_cond || is_protected_modifier_cond) {
//                if (this->scope_ptr->visibility_type == AIO_VISIBILITY_UNDEFINED) {
//                    if (is_private_modifier_cond) {
//                        this->scope_ptr->visibility_type = AIO_VISIBILITY_PRIVATE;
//                    }
//                    if (is_protected_modifier_cond) {
//                        this->scope_ptr->visibility_type = AIO_VISIBILITY_PROTECTED;
//                    }
//                } else {
//                    throw_error_with_tag(AIO_SCOPE_PARTICLE_ERROR_TAG, "Visibility attribute already specified!");
//                }
//            }
            this->switch_monitor_mode(symbol, position);
        } else {
            //Maybe is annotation:
//            const bool starts_as_annotation = this->token_holder->get_relative_char(0) == '@';
//            this->token_holder->start++;
//            const bool is_valid_name = starts_as_annotation && this->token_holder->is_word()
//                                       && is_not_aio_modifier(this->token_holder);
//            if (is_valid_name) {
//                this->scope_ptr->annotation_names->add(new str_hook(this->token_holder));
//            } else {
//                this->token_holder->start--;
//                throw_error_with_str_hook(AIO_SCOPE_PARTICLE_ERROR_TAG, "Invalid attribute", this->token_holder);
//            }
        }
        this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    }
}


#define OPENING_BRACE '{'

#define CLOSING_BRACE '}'

void aio_scope_particle::monitor_scope_body(const char symbol, const unsigned position)
{
//    str_hook class_body_holder = explore_hook_scope(position, OPENING_BRACE, CLOSING_BRACE, hook);
//    aio_orbit<aio_scope> *scope_orbit = new aio_scope_orbit(this->scope, this->runtime_ptr);
//    Fill the same class:
//    this->scope = scope_orbit->spin(hook);
//    this->signal = AIO_PARTICLE_SIGNAL_IS_READY;
//    ------------------------------------------------------------------------------------------------------------------
//    delete scope_orbit;
}

void aio_scope_particle::switch_monitor_mode(const char symbol, const unsigned position)
{
    const bool is_colon_cond = is_colon(symbol);
    const bool is_semicolon_cond = is_semicolon(symbol);
    const bool is_opening_brace_cond = is_opening_brace(symbol);
    if (is_semicolon_cond) {
        this->signal = AIO_PARTICLE_SIGNAL_IS_READY;
    } else if (is_colon_cond) {
        //Attribute class mode:
        this->monitor_mode = AIO_MONITOR_ATTRIBUTES;
    } else if (is_opening_brace_cond) {
        //Body class mode:
        this->monitor_mode = AIO_MONITOR_BODY;
    } else {
        throw_error_with_tag(AIO_SCOPE_PARTICLE_ERROR_TAG, "Invalid state!");
    }
}

unsigned aio_scope_particle::illuminate(aio_space *space)
{
    //Set field:
    space->pathnames->add(this->scope_ptr);
    this->scope_ptr= nullptr;
    return this->token_holder->end;
}

//
//array_list<aio_particle<aio_scope>> *particle_list = new array_list<aio_particle<aio_scope>>();
//particle_list->add(new aio_class_particle<aio_scope>(runtime_ptr, scope_ptr->typenames));
////    particle_list->add(new aio_field_particle<aio_scope>(runtime_ptr->get_types(), scope_ptr->fields));
//particle_list->add(new aio_scope_particle<aio_scope>(runtime_ptr, scope_ptr->pathnames));
//particle_list->add(new aio_function_particle<aio_scope>(runtime_ptr, scope_ptr->functions));
//return particle_list;