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
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>
#include <lib4aio_cpp_headers/aio_orbit/aio_orbit.h>

/**
 * Tags.
 */

#define AIO_CLASS_PARTICLE_INFO_TAG "AIO_CLASS_PARTICLE_INFO"

#define AIO_CLASS_PARTICLE_ERROR_TAG "AIO_CLASS_PARTICLE_ERROR"

#define AIO_CLASS_PARTICLE_DEBUG

aio_class_particle::aio_class_particle()
{
    this->clazz = new aio_class();
    this->monitor_mode = AIO_MONITOR_MODIFIER;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    this->signal = AIO_PARTICLE_SIGNAL_UNDEFINED;
}

aio_class_particle::~aio_class_particle()
{
    delete this->clazz;
}

void aio_class_particle::reset()
{
    aio_class *old_clazz = this->clazz;
    this->clazz = new aio_class();
    this->counter_trigger = 0;
    this->monitor_mode = AIO_MONITOR_MODIFIER;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    this->signal = AIO_PARTICLE_SIGNAL_UNDEFINED;
    delete old_clazz;
}

unsigned aio_class_particle::illuminate(aio_space *space)
{
    //TODO: Make put for schemable:
    space->typenames->add(this->clazz);
    this->clazz = new aio_class();
#ifdef AIO_CLASS_PARTICLE_DEBUG
    log_info(AIO_CLASS_PARTICLE_INFO_TAG, "COMPLETE!");
#endif
    this->token_holder->start = this->token_holder->end;
    return this->token_holder->end;
}

const aio_particle_signal aio_class_particle::handle_symbol(const unsigned position)
{
    const char symbol = this->radius_ptr->get_string()[position];
    switch (this->monitor_mode) {

        case AIO_MONITOR_MODIFIER:
            this->monitor_modifier(symbol, position);
            break;
        case AIO_MONITOR_NAME:
            this->monitor_name(symbol, position);
            break;
        case AIO_MONITOR_ARROW_OR_COLON_OR_OPENING_BRACE:
            this->monitor_arrow_or_colon_or_opening_brace(symbol, position);
            break;
        case AIO_MONITOR_PARENT:
            this->monitor_parent(symbol, position);
            break;
        case AIO_MONITOR_COMMA_OR_COLON_OR_OPENING_BRACE:
            this->monitor_comma_or_colon_or_opening_brace(symbol, position);
            break;
        case AIO_MONITOR_ATTRIBUTE:
            this->monitor_attribute(symbol, position);
            break;
        case AIO_MONITOR_COLON_OR_OPENING_BRACE:
            this->monitor_colon_or_opening_brace(symbol, position);
            break;
        case AIO_MONITOR_BODY:
            this->monitor_body(symbol, position);
    }
    return this->signal;
}

void aio_class_particle::monitor_modifier(const char symbol, const unsigned position)
{
    const bool is_separator_cond = is_space_or_line_break(symbol);
    switch (this->trigger_mode) {
        case AIO_TRIGGER_MODE_PASSIVE:
            if (!is_separator_cond) {
                this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                this->token_holder->start = position;
            }
            break;
        case AIO_TRIGGER_MODE_ACTIVE: {
            if (is_separator_cond) {
                //Capture modifier:
                this->token_holder->end = position;
#ifdef AIO_CLASS_PARTICLE_DEBUG
                log_info_str_hook(AIO_CLASS_PARTICLE_INFO_TAG, "Modifier:", this->token_holder);
#endif
                if (is_aio_class_modifier(this->token_holder)) {
                    //Go to name state:
                    this->go_to_name_state();
                }
            }
        }
    }
}

void aio_class_particle::monitor_name(const char symbol, const unsigned position)
{
    switch (this->trigger_mode) {
        case AIO_TRIGGER_MODE_PASSIVE:
            if (!is_space_or_line_break(symbol)) {
                if (isalpha(symbol)) {
                    this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                    this->token_holder->start = position;
                } else {
                    throw_error_with_tag(AIO_CLASS_PARTICLE_ERROR_TAG, "The class name must start with letter!");
                }
            }
            break;
        case AIO_TRIGGER_MODE_ACTIVE:
            if (!isalnum(symbol)) {
                //Capture name:
                this->token_holder->end = position;
#ifdef AIO_CLASS_PARTICLE_DEBUG
                log_info_str_hook(AIO_CLASS_PARTICLE_ERROR_TAG, "Token name:", this->token_holder);
#endif
                //Set name for field:
                this->clazz->name = new str_hook(this->token_holder);
                //Switch to [<type>:=]:
                this->go_to_arrow_or_colon_or_opening_brace_state(symbol, position);
            }
    }
}

void aio_class_particle::monitor_arrow_or_colon_or_opening_brace(const char symbol, const unsigned position)
{
    switch (this->trigger_mode) {
        case AIO_TRIGGER_MODE_PASSIVE:
            if (is_colon(symbol)) {
                //Capture ':':
                //Switch to 'private|protected|abstract|open':
                this->go_to_attribute_state();
            } else if (is_opening_brace(symbol)) {
                //Capture '{':
                this->go_to_body_state(symbol, position);
            } else if (!is_space_or_line_break(symbol)) {
                if (is_less_sign(symbol)) {
                    //Capture "<-"
                    this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                } else {
                    throw_error_with_tag(AIO_CLASS_PARTICLE_ERROR_TAG, "Expected ':' or '<-' or '{'");
                }
            }
            break;
        case AIO_TRIGGER_MODE_ACTIVE:
            if (is_hyphen(symbol)) {
                //'-':
                //Capture parent:
                this->go_to_parent_state();
            } else {
                throw_error_with_tag(AIO_CLASS_PARTICLE_ERROR_TAG, "Expected <-");
            }
    }
}

void aio_class_particle::monitor_attribute(const char symbol, const unsigned position)
{
    switch (this->trigger_mode) {
        case AIO_TRIGGER_MODE_PASSIVE:
            if (!is_space_or_line_break(symbol)) {
                this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                this->token_holder->start = position;
            }
            break;
        case AIO_TRIGGER_MODE_ACTIVE:
            if (!isalnum(symbol)) {
                //Capture attribute:
                this->token_holder->end = position;
#ifdef AIO_CLASS_PARTICLE_DEBUG
                log_info_str_hook(AIO_CLASS_PARTICLE_INFO_TAG, "Attribute:", this->token_holder);
#endif
                //Check attribute:
                const bool is_private = is_aio_private_modifier(this->token_holder);
                const bool is_protected = is_aio_protected_modifier(this->token_holder);
                const bool is_abstract = is_aio_abstract_modifier(this->token_holder);
                const bool is_open = is_aio_open_modifier(this->token_holder);
                if (is_private || is_protected) {
                    if (this->clazz->visibility_type == AIO_VISIBILITY_UNDEFINED) {
                        //Set attribute:
                        if (is_private) {
                            this->clazz->visibility_type = AIO_VISIBILITY_PRIVATE;
                        } else {
                            this->clazz->visibility_type = AIO_VISIBILITY_PROTECTED;
                        }
                        //Switch to [:{]:
                        this->go_to_colon_or_opening_brace_state(symbol, position);
                    } else {
                        throw_error_with_tag(
                                AIO_CLASS_PARTICLE_ERROR_TAG, "Class visibility is already defined!"
                        );
                    }
                } else if (is_abstract || is_open) {
                    if (this->clazz->inherited_type == AIO_INHERITED_TYPE_UNDEFINED) {
                        //Set attribute:
                        if (is_abstract) {
                            this->clazz->inherited_type = AIO_INHERITED_TYPE_ABSTRACT;
                        } else {
                            this->clazz->inherited_type = AIO_INHERITED_TYPE_OPEN;
                        }
                        //Switch to [:{]:
                        this->go_to_colon_or_opening_brace_state(symbol, position);
                    } else {
                        throw_error_with_tag(
                                AIO_CLASS_PARTICLE_ERROR_TAG, "Class inherited type is already defined!"
                        );
                    }
                } else {
                    throw_error_with_tag(
                            AIO_CLASS_PARTICLE_ERROR_TAG,
                            "Expected attribute 'protected', 'private', 'abstract', 'open'"
                    );
                }
            }
    }
}

void aio_class_particle::monitor_parent(const char symbol, const unsigned position)
{
    switch (this->trigger_mode) {
        case AIO_TRIGGER_MODE_PASSIVE:
            if (!is_space_or_line_break(symbol)) {
                this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                this->token_holder->start = position;
            }
            break;
        case AIO_TRIGGER_MODE_ACTIVE:
            if (!isalnum(symbol)) {
                //Capture attribute:
                this->token_holder->end = position;
#ifdef AIO_CLASS_PARTICLE_DEBUG
                log_info_str_hook(AIO_CLASS_PARTICLE_INFO_TAG, "Parent:", this->token_holder);
#endif
                //Check attribute:
                if (this->token_holder->is_word()) {
                    this->clazz->parent_names->add(new str_hook(this->token_holder));
                    this->go_to_comma_or_colon_or_opening_brace_state(symbol, position);
                } else {
                    throw_error_with_tag(AIO_CLASS_PARTICLE_ERROR_TAG, "Expected parent class name");
                }
            }
    }
}

void aio_class_particle::monitor_comma_or_colon_or_opening_brace(const char symbol, const unsigned position)
{
    if (is_comma(symbol)) {
        //Capture ',':
        this->go_to_parent_state();
    } else if (is_colon(symbol)) {
        //Capture ':':
        this->go_to_attribute_state();
    } else if (is_opening_brace(symbol)) {
        //Capture '{':
        this->go_to_body_state(symbol, position);
    } else if (!is_space_or_line_break(symbol)) {
        throw_error_with_tag(AIO_CLASS_PARTICLE_ERROR_TAG, "Expected [,:{]");
    }
}

void aio_class_particle::monitor_colon_or_opening_brace(const char symbol, const unsigned position)
{
    if (is_colon(symbol)) {
        //Capture ':':
        this->go_to_attribute_state();
    } else if (is_opening_brace(symbol)) {
        //Capture '{':
        this->go_to_body_state(symbol, position);
    } else if (!is_space_or_line_break(symbol)) {
        throw_error_with_tag(AIO_CLASS_PARTICLE_ERROR_TAG, "Expected [:{]");
    }
}

void aio_class_particle::monitor_body(const char symbol, const unsigned position)
{
    const bool is_opening_brace_cond = is_opening_brace(symbol);
    switch (this->trigger_mode) {
        case AIO_TRIGGER_MODE_PASSIVE:
            if (is_opening_brace_cond) {
                this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                //Take start of args content without '{':
                this->token_holder->start = position + 1;
                this->counter_trigger++;
            } else if (!is_space_or_line_break(symbol)) {
                throw_error_with_tag(AIO_CLASS_PARTICLE_ERROR_TAG, "Expected opening brace or separator!");
            }
            break;
        case AIO_TRIGGER_MODE_ACTIVE:
            if (is_opening_brace_cond) {
                this->counter_trigger++;
            } else if (is_closing_brace(symbol)) {
                this->counter_trigger--;
                if (this->counter_trigger == 0) {
                    this->token_holder->end = position;
                    this->set_body();
                }
            }
            break;
    }
}

void aio_class_particle::go_to_name_state()
{
    this->monitor_mode = AIO_MONITOR_NAME;
    this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
}

void aio_class_particle::go_to_arrow_or_colon_or_opening_brace_state(const char symbol, const unsigned position)
{
    this->monitor_mode = AIO_MONITOR_ARROW_OR_COLON_OR_OPENING_BRACE;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    this->monitor_arrow_or_colon_or_opening_brace(symbol, position);
}

void aio_class_particle::go_to_attribute_state()
{
    this->monitor_mode = AIO_MONITOR_ATTRIBUTE;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
}

void aio_class_particle::go_to_body_state(const char symbol, const unsigned position)
{
    this->monitor_mode = AIO_MONITOR_BODY;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    //Prepare counter:
    this->counter_trigger = 0;
    this->monitor_body(symbol, position);
}

void aio_class_particle::go_to_parent_state()
{
    this->monitor_mode = AIO_MONITOR_PARENT;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
}

void aio_class_particle::go_to_comma_or_colon_or_opening_brace_state(const char symbol, const unsigned position)
{
    this->monitor_mode = AIO_MONITOR_COMMA_OR_COLON_OR_OPENING_BRACE;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    this->monitor_comma_or_colon_or_opening_brace(symbol, position);
}

void aio_class_particle::go_to_colon_or_opening_brace_state(const char symbol, const unsigned position)
{
    this->monitor_mode = AIO_MONITOR_COLON_OR_OPENING_BRACE;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    this->monitor_colon_or_opening_brace(symbol, position);
}

void aio_class_particle::set_body()
{
    //Launch particles:
    aio_orbit<aio_schemable>::create()
            ->set_pivot(this->clazz)
            ->set_radius(new str_hook(this->token_holder))
//            ->set_particle()
//            ->spin()
            ->finish();
    this->signal = AIO_PARTICLE_SIGNAL_IS_READY;

#ifdef AIO_CLASS_PARTICLE_DEBUG
    log_info(AIO_CLASS_PARTICLE_INFO_TAG, "BODY IS COMPLETE!");
#endif
}