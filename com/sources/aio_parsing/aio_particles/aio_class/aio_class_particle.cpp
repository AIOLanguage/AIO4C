//lang:
#include <aio_lang/aio_space/aio_space.h>
#include <aio_lang/aio_modifiers/aio_modifiers.h>
#include <aio_lang/aio_space/aio_initializable/aio_class/aio_class.h>
//parsing:
#include <aio_parsing/aio_particles/aio_class/aio_class_particle.h>
//lib4aio:
#include <lib4aio_cpp_headers/aio_explorer/aio_explorer.h>
#include <lib4aio_cpp_headers/utils/char_utils/char_utils.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>
#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>
#include <lib4aio_cpp_sources/aio_orbit/aio_particle/aio_particle.cpp>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

/**
 * Tags.
 */

#define AIO_CLASS_PARTICLE_INFO_TAG "AIO_CLASS_PARTICLE_INFO"

#define AIO_CLASS_PARTICLE_ERROR_TAG "AIO_CLASS_PARTICLE_ERROR"

#define AIO_CLASS_PARTICLE_DEBUG

aio_class_particle::aio_class_particle()
{}

aio_class_particle::~aio_class_particle()
{}

const aio_particle_signal aio_class_particle::handle_symbol(const unsigned position)
{
    if (position > this->inner_iterator) {
        this->inner_iterator = position;
        const char symbol = this->radius_ptr->get_string()[position];
        switch (this->monitor_mode) {
            case AIO_MONITOR_MODIFIER:
                this->monitor_class_modifier(symbol, position);
                break;
            case AIO_MONITOR_NAME:
                this->monitor_class_name(symbol, position);
                break;
            case AIO_MONITOR_KEY:
                this->monitor_class_key(symbol, position);
                break;
            case AIO_MONITOR_PARENTS:
                this->monitor_class_parents(symbol, position);
                break;
            case AIO_MONITOR_ATTRIBUTES:
                this->monitor_class_attributes(symbol, position);
                break;
            case AIO_MONITOR_BODY:
                this->monitor_class_body(symbol, position);
                break;
        }
    }
    return this->signal;
}

void aio_class_particle::monitor_class_modifier(const char symbol, const unsigned position)
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
        const bool is_class_modifier = is_aio_class_modifier(this->token_holder);
        if (is_class_modifier) {
#ifdef AIO_CLASS_PARTICLE_DEBUG
            log_info_str_hook(AIO_CLASS_PARTICLE_INFO_TAG, "Found modifier:", this->token_holder);
#endif
            this->class_ptr = new aio_class();
            //Prepare to the next state:
            this->monitor_mode = AIO_MONITOR_NAME;
            this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
            this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
        }
    }
}

void aio_class_particle::monitor_class_name(const char symbol, const unsigned position)
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
    const bool is_arrow_cond = is_less_sign(symbol);
    const bool is_token_scan_finished = (is_whitespace_cond || is_semicolon_cond || is_colon_cond || is_arrow_cond)
                                        && this->trigger_mode == AIO_TRIGGER_MODE_ACTIVE;
    if (is_token_scan_finished) {
        this->token_holder->end = position;
        const bool is_valid_class_name = this->token_holder->is_word();
//                && !this->class_list_ptr->contains_by(
//                [this](aio_class *it) -> bool {
//                    return it->name->equals_string(this->token_holder);
//                });
        if (is_valid_class_name) {
#ifdef AIO_CLASS_PARTICLE_DEBUG
            log_info_str_hook(AIO_CLASS_PARTICLE_INFO_TAG, "Found name:", this->token_holder);
#endif
            this->class_ptr->name = new str_hook(this->token_holder);
            this->switch_monitor_mode(symbol, position);
            this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
        }
    }
}

void aio_class_particle::monitor_class_key(const char symbol, const unsigned position)
{
    const bool is_whitespace = is_space_or_line_break(symbol);
    if (!is_whitespace) {
        this->switch_monitor_mode(symbol, position);
    }
}

void aio_class_particle::switch_monitor_mode(const char symbol, const unsigned position)
{
    const bool is_colon_cond = is_colon(symbol);
    const bool is_arrow_cond = is_less_sign(symbol);
    const bool is_semicolon_cond = is_semicolon(symbol);
    const bool is_opening_brace_cond = is_opening_brace(symbol);
    const bool is_comma_cond = is_comma(symbol);
    if (is_semicolon_cond) {
        this->signal = AIO_PARTICLE_SIGNAL_IS_READY;
    } else if (is_colon_cond) {
        //Attribute class mode:
        this->monitor_mode = AIO_MONITOR_ATTRIBUTES;
    } else if (is_opening_brace_cond) {
        this->monitor_mode = AIO_MONITOR_BODY;
    } else if (is_comma_cond && this->monitor_mode == AIO_MONITOR_PARENTS) {
        //Nothing:
    } else if (is_arrow_cond) {
        //Maybe this is parent class mode:
        const unsigned next_position = position + 1;
        const bool is_arrow = next_position < this->radius_ptr->end
                              && is_hyphen(this->radius_ptr->get_string()[next_position]);
        if (is_arrow) {
            this->monitor_mode = AIO_MONITOR_PARENTS;
            this->inner_iterator++;
        } else {
            throw_error_with_tag(AIO_CLASS_PARTICLE_ERROR_TAG, "Invalid symbol, maybe you mean '<-'");
        }
    } else {
        throw_error_with_tag(AIO_CLASS_PARTICLE_ERROR_TAG, "Invalid state!");
    }
}

void aio_class_particle::monitor_class_parents(const char symbol, const unsigned position)
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
    const bool is_comma_cond = is_comma(symbol);
    const bool is_token_scan_finished = (is_whitespace_cond || is_semicolon_cond || is_colon_cond || is_comma_cond)
                                        && this->trigger_mode == AIO_TRIGGER_MODE_ACTIVE;
    if (is_token_scan_finished) {
        this->token_holder->end = position;
        const bool is_valid_parent_class_name = this->token_holder->is_word()
                                                && is_not_aio_modifier(this->token_holder);
        if (is_valid_parent_class_name) {
#ifdef AIO_CLASS_PARTICLE_DEBUG
            log_info_str_hook(AIO_CLASS_PARTICLE_INFO_TAG, "Found temp_parent:", this->token_holder);
#endif
            aio_class *temp_parent = new aio_class();
            temp_parent->name = new str_hook(this->token_holder);
            this->class_ptr->parents->add(temp_parent);
            this->switch_monitor_mode(symbol, position);
            this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
        }
    }
}

void aio_class_particle::monitor_class_attributes(const char symbol, const unsigned position)
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
    const bool is_comma_cond = is_comma(symbol);
    const bool is_token_scan_finished = (is_whitespace_cond || is_semicolon_cond || is_colon_cond || is_comma_cond)
                                        && this->trigger_mode == AIO_TRIGGER_MODE_ACTIVE;
    if (is_token_scan_finished) {
        this->token_holder->end = position;
        const bool is_open_modifier_cond = is_aio_open_modifier(this->token_holder);
        const bool is_abstract_modifier_cond = is_aio_abstract_modifier(this->token_holder);
        const bool is_protected_modifier_cond = is_aio_protected_modifier(this->token_holder);
        const bool is_private_modifier_cond = is_aio_private_modifier(this->token_holder);
        const bool is_attribute_keyword = is_open_modifier_cond || is_abstract_modifier_cond
                                          || is_protected_modifier_cond || is_private_modifier_cond;
        if (is_attribute_keyword) {
#ifdef AIO_CLASS_PARTICLE_DEBUG
            log_info_str_hook(AIO_CLASS_PARTICLE_INFO_TAG, "Found attribute:", this->token_holder);
#endif
            if (is_private_modifier_cond || is_protected_modifier_cond) {
                if (this->class_ptr->visibility_type == AIO_VISIBILITY_UNDEFINED) {
                    if (is_private_modifier_cond) {
                        this->class_ptr->visibility_type = AIO_VISIBILITY_PRIVATE;
                    }
                    if (is_protected_modifier_cond) {
                        this->class_ptr->visibility_type = AIO_VISIBILITY_PROTECTED;
                    }
                } else {
                    throw_error_with_tag(AIO_CLASS_PARTICLE_ERROR_TAG, "Visibility attribute already specified!");
                }
            }
            if (is_open_modifier_cond || is_abstract_modifier_cond) {
                if (this->class_ptr->inherited_type == AIO_INHERITED_TYPE_UNDEFINED) {
                    if (is_open_modifier_cond) {
                        this->class_ptr->inherited_type = AIO_INHERITED_TYPE_OPEN;
                    }
                    if (is_abstract_modifier_cond) {
                        this->class_ptr->inherited_type = AIO_INHERITED_TYPE_ABSTRACT;
                    }
                } else {
                    throw_error_with_tag(AIO_CLASS_PARTICLE_ERROR_TAG, "Inherited attribute already specified!");
                }
            }
            this->switch_monitor_mode(symbol, position);
        } else {
            //Maybe is annotation:
//            const bool starts_as_annotation = this->token_holder->get_relative_char(0) == '@';
//            this->token_holder->start++;
//            const bool is_valid_name = starts_as_annotation && this->token_holder->is_word()
//                                       && is_not_aio_modifier(this->token_holder);
//            if (is_valid_name) {
//                Create temp annotation:
//                aio_class
//                this->class_ptr->annotation_names->add(new str_hook(this->token_holder));
//            } else {
//                this->token_holder->start--;
//                throw_error_with_str_hook(AIO_CLASS_PARTICLE_ERROR_TAG, "Invalid attribute", this->token_holder);
//            }
        }
        this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    }
}

#define OPENING_BRACE '{'

#define CLOSING_BRACE '}'

void aio_class_particle::monitor_class_body(const char symbol, const unsigned position)
{
    str_hook class_body_holder = explore_hook_scope(position, OPENING_BRACE, CLOSING_BRACE, this->radius_ptr);
//    aio_orbit<aio_class> *class_orbit = new aio_class_orbit(this->class_ptr, this->runtime_ptr);
    //Fill the same class:
//    this->class_ptr = class_orbit->spin(hook);
    this->signal = AIO_PARTICLE_SIGNAL_IS_READY;
}

unsigned aio_class_particle::illuminate(aio_space *space)
{
    //Set field:
    space->typenames->add(this->class_ptr);
    this->class_ptr = nullptr;
    return this->token_holder->end;
}


//
//array_list<aio_particle<aio_class>> *particle_list = new array_list<aio_particle<aio_class>>();
//particle_list->add(new aio_class_particle<aio_class>(runtime_ptr, class_ptr->typenames));
//particle_list->add(new aio_field_particle<aio_class>(runtime_ptr->get_types(), class_ptr->fields.txt));
//particle_list->add(new aio_scope_particle<aio_class>(runtime_ptr, class_ptr->pathnames));
//particle_list->add(new aio_function_particle<aio_class>(runtime_ptr, class_ptr->functions));
//particle_list->add(new aio_constructor_particle<aio_class>(runtime_ptr, class_ptr->constructors));
//