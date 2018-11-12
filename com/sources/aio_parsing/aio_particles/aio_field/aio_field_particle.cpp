//native:
#include <cctype>
#include <typeinfo>
//lang:
#include <aio_lang/aio_space/aio_space.h>
#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_types/aio_types.h>
#include <aio_lang/aio_visible/aio_visible.h>
#include <aio_lang/aio_schemable/aio_schemable.h>
#include <aio_lang/aio_modifiers/aio_modifiers.h>
//parsing:
#include <aio_parsing/aio_particles/aio_field/aio_field_particle.h>
//runtime:
#include <aio_runtime/aio_task/aio_assign/aio_assign_task.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/string_utils/common.h>
#include <lib4aio_cpp_headers/utils/char_utils/char_utils.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>
#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>
#include <lib4aio_cpp_sources/aio_orbit/aio_particle/aio_particle.cpp>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

/**
 * 태그들.
 */

#define AIO_FIELD_PARTICLE_DEBUG

#define AIO_FIELD_PARTICLE_ERROR_TAG "AIO_FIELD_PARTICLE_ERROR"

#ifdef AIO_FIELD_PARTICLE_DEBUG

#define AIO_FIELD_PARTICLE_INFO_TAG "AIO_FIELD_PARTICLE_INFO"

#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>

#endif

/**
 * 비즈니스 러직.
 */

using namespace lib4aio;

aio_field_particle::aio_field_particle()
{
    this->reset();
}

aio_field_particle::~aio_field_particle()
{
    delete this->task;
    delete this->field;
}

void aio_field_particle::recycle()
{
    aio_assign_task *old_task = this->task;
    aio_field *old_field = this->field;
    delete old_task;
    delete old_field;
    this->reset();
}

void aio_field_particle::reset()
{
    this->field = new aio_field();
    this->field->is_static = false;
    this->field->is_array = false;
    this->task = new aio_assign_task();
    this->monitor_mode = AIO_MONITOR_MODIFIER;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    this->signal = AIO_PARTICLE_SIGNAL_UNDEFINED;
    this->whitespace_counter = 0;
}

/**
 * Handles symbol in finite-state machine.
 */

const aio_particle_signal aio_field_particle::handle_symbol(const unsigned position)
{
    const char symbol = this->radius_ptr->get_string()[position];
    switch (this->monitor_mode) {
        case AIO_MONITOR_MODIFIER:
            this->monitor_modifier(symbol, position);
            break;
        case AIO_MONITOR_NAME:
            this->monitor_name(symbol, position);
            break;
        case AIO_MONITOR_TYPE_OR_COLON_OR_EQUAL_SIGN:
            this->monitor_type_or_colon_or_equal_sign(symbol, position);
            break;
        case AIO_MONITOR_ATTRIBUTE:
            this->monitor_attribute(symbol, position);
            break;
        case AIO_MONITOR_COLON_OR_EQUAL_SIGN_OR_SEMICOLON:
            this->monitor_colon_or_equal_sign_or_semicolon(symbol, position);
            break;
        case AIO_MONITOR_VALUE:
            this->monitor_value(symbol, position);
            break;
    }
    return this->signal;
}

void aio_field_particle::monitor_modifier(const char symbol, const unsigned position)
{
    const bool is_separator_cond = is_space_or_line_break(symbol);
    switch (this->trigger_mode) {
        case AIO_TRIGGER_MODE_PASSIVE:
            if (!is_separator_cond) {
                this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                this->token_holder->start = position;
            }
            break;
        case AIO_TRIGGER_MODE_ACTIVE:
            if (is_separator_cond) {
                //Capture modifier:
                this->token_holder->end = position;

                //Go to name state:
                this->go_to_name_state();

#ifdef AIO_FIELD_PARTICLE_DEBUG
                log_info_str_hook(AIO_FIELD_PARTICLE_INFO_TAG, "Modifier:", this->token_holder);
#endif
                const bool is_constant_modifier = is_aio_constant_modifier(this->token_holder);
                const bool is_variable_modifier = is_aio_variable_modifier(this->token_holder);
                if (is_constant_modifier || is_variable_modifier) {
                    //Create new field:
                    if (is_constant_modifier) {
                        this->field->is_const = true;
                    }
                    if (is_variable_modifier) {
                        this->field->is_const = false;
                    }
#ifdef AIO_FIELD_PARTICLE_DEBUG
                    log_info_boolean(AIO_FIELD_PARTICLE_INFO_TAG, "Is constant", this->field->is_const);
#endif
                } else {
                    //Ok, try to reinterpret stream from name state:
#ifdef AIO_FIELD_PARTICLE_DEBUG
                    log_info(AIO_FIELD_PARTICLE_INFO_TAG, "TRY TO REINTERPRET STREAM");
#endif
                    for (unsigned i = this->token_holder->start; i <= this->token_holder->end; ++i) {
                        this->handle_symbol(i);
                    }
                }
            }
    }
}

void aio_field_particle::go_to_name_state()
{
    this->monitor_mode = AIO_MONITOR_NAME;
    this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
}

void aio_field_particle::monitor_name(const char symbol, const unsigned position)
{
    switch (this->trigger_mode) {
        case AIO_TRIGGER_MODE_PASSIVE:
            if (!is_space_or_line_break(symbol)) {
                if (isalpha(symbol)) {
                    this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                    this->token_holder->start = position;
                }
            }
            break;
        case AIO_TRIGGER_MODE_ACTIVE:
            if (!isalnum(symbol)) {
                //Capture name:
                this->token_holder->end = position;
#ifdef AIO_FIELD_PARTICLE_DEBUG
                log_info_str_hook(AIO_FIELD_PARTICLE_INFO_TAG, "Token name:", this->token_holder);
#endif
                //Set name for field:
                this->field->name = new str_hook(this->token_holder);
                //Set name for task:
                this->task->set_name(new str_hook(this->token_holder));
                //Switch to [<type>:=]:
                this->go_to_type_or_colon_or_equal_sign_state(symbol, position);
            }
    }
}

void aio_field_particle::go_to_type_or_colon_or_equal_sign_state(const char symbol, const unsigned position)
{
    this->monitor_mode = AIO_MONITOR_TYPE_OR_COLON_OR_EQUAL_SIGN;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    this->monitor_type_or_colon_or_equal_sign(symbol, position);
}

#define ARRAY_BRACKETS "[]"

#define ARRAY_BRACKET_SIZE 2

void aio_field_particle::monitor_type_or_colon_or_equal_sign(const char symbol, const unsigned position)
{
    switch (this->trigger_mode) {
        case AIO_TRIGGER_MODE_PASSIVE:
            if (is_equal_sign(symbol)) {
                //Capture '=':
                this->go_to_value_state(position);
            } else if (is_colon(symbol)) {
                //Capture ':':
                //Switch to 'private|protected':
                this->go_to_attribute_state();
            } else if (!is_space_or_line_break(symbol)) {
                if (isalpha(symbol)) {
                    //Collect <type>:
                    this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                    this->token_holder->start = position;
                } else {
                    throw_error_with_tag(AIO_FIELD_PARTICLE_ERROR_TAG, "The field type must start with letter!");
                }
            }
            break;
        case AIO_TRIGGER_MODE_ACTIVE:
            if (!isalnum(symbol) && !is_opening_bracket(symbol) && !is_closing_bracket(symbol)) {
                //Capture type:
                this->token_holder->end = position;
                //Get type:
                str_hook *type = new str_hook(this->token_holder);
                //Check type:
                const bool is_array = type->ends_with(ARRAY_BRACKETS);
                if (is_array) {
                    type->end -= ARRAY_BRACKET_SIZE;
                    if (!type->is_word()) {
                        throw_error_with_tag(
                                AIO_FIELD_PARTICLE_ERROR_TAG, "The field type must contain only letters & numbers!"
                        );
                    }
                }
                //Set type to field:
                this->field->type = type;
                this->field->is_array = is_array;
                //Switch to [:=;]:
                this->go_to_colon_or_equal_sign_or_semicolon_state(symbol, position);
            }
    }
}

void aio_field_particle::go_to_value_state(const unsigned position)
{
    this->monitor_mode = AIO_MONITOR_VALUE;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
    this->token_holder->start = position + 1;
}

void aio_field_particle::go_to_attribute_state()
{
    this->monitor_mode = AIO_MONITOR_ATTRIBUTE;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
}

void aio_field_particle::go_to_colon_or_equal_sign_or_semicolon_state(const char symbol, const unsigned position)
{
    this->monitor_mode = AIO_MONITOR_COLON_OR_EQUAL_SIGN_OR_SEMICOLON;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    this->monitor_colon_or_equal_sign_or_semicolon(symbol, position);
}

void aio_field_particle::monitor_attribute(const char symbol, const unsigned position)
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
#ifdef AIO_FIELD_PARTICLE_DEBUG
                log_info_str_hook(AIO_FIELD_PARTICLE_INFO_TAG, "Attribute:", this->token_holder);
#endif
                //Check attribute:
                const bool is_private = is_aio_private_modifier(this->token_holder);
                const bool is_protected = is_aio_protected_modifier(this->token_holder);
                if (is_private || is_protected) {
                    if (this->field->visibility == aio_visible::AIO_VISIBILITY_UNDEFINED) {
                        //Set attribute:
                        if (is_private) {
                            this->field->visibility = aio_visible::AIO_VISIBILITY_PRIVATE;
                        } else {
                            this->field->visibility = aio_visible::AIO_VISIBILITY_PROTECTED;
                        }
                        //Switch to [:=;]:
                        this->go_to_colon_or_equal_sign_or_semicolon_state(symbol, position);
                    } else {
                        throw_error_with_tag(AIO_FIELD_PARTICLE_ERROR_TAG, "Field visibility is already defined!");
                    }
                } else {
                    throw_error_with_tag(AIO_FIELD_PARTICLE_ERROR_TAG, "Expected attribute 'protected' or 'private'");
                }
            }
    }
}

void aio_field_particle::monitor_colon_or_equal_sign_or_semicolon(const char symbol, const unsigned position)
{
    if (is_equal_sign(symbol)) {
        //Capture '=':
        this->go_to_value_state(position);
    } else if (is_colon(symbol)) {
        //Capture ':':
        this->go_to_attribute_state();
    } else if (is_semicolon(symbol)) {
        //Capture ';':
        this->set_null();
    } else if (!is_space_or_line_break(symbol)) {
        throw_error_with_tag(AIO_FIELD_PARTICLE_ERROR_TAG, "Expected [=:;]");
    }
}

void aio_field_particle::set_null()
{
#ifdef AIO_FIELD_PARTICLE_DEBUG
    log_info(AIO_FIELD_PARTICLE_INFO_TAG, "Put null in task");
#endif
    this->task->set_value(nullptr);
    this->signal = AIO_PARTICLE_SIGNAL_IS_READY;
}

void aio_field_particle::monitor_value(const char symbol, const unsigned position)
{
    const bool is_single_quote_cond = is_single_quote(symbol);
    if (is_single_quote_cond) {
        this->is_inside_string = !this->is_inside_string;
    }
    const bool in_expression_scope = !this->is_inside_string;
    const bool is_end_of_holder = position == this->radius_ptr->end - 1;
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    const bool is_letter_or_number = isalnum(symbol);
    if (is_end_of_holder) {
        this->set_value(true, position);
    }
    if (in_expression_scope) {
        switch (this->trigger_mode) {
            case AIO_TRIGGER_MODE_PASSIVE:
                if (is_letter_or_number || is_closing_parenthesis(symbol) || is_single_quote_cond) {
                    this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                    this->whitespace_counter = 0;

                }
                break;
            case AIO_TRIGGER_MODE_ACTIVE:
                if (is_whitespace_cond) {
                    this->whitespace_counter++;
                } else if (is_sign(symbol)) {
                    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
                    this->whitespace_counter = 0;
                } else if ((is_letter_or_number && this->whitespace_counter > 0) || is_closing_brace(symbol)) {
                    this->set_value(false, position);
                }
        }
    }
}

void aio_field_particle::set_value(const bool is_end_of_holder, const unsigned position)
{
    if (is_end_of_holder) {
        this->token_holder->end = this->radius_ptr->end;
    } else {
        this->token_holder->end = position - this->whitespace_counter;
    }
    char *dirty_value = this->token_holder->to_string();
    char *clean_value = squeeze_string_for_expression(dirty_value);
#ifdef AIO_FIELD_PARTICLE_DEBUG
    log_info_string(AIO_FIELD_PARTICLE_INFO_TAG, "Value:", clean_value);
#endif
    this->task->set_value(clean_value);
    this->token_holder->start = this->token_holder->end;
    this->signal = AIO_PARTICLE_SIGNAL_IS_READY;
    //------------------------------------------------------------------------------------------------------------------
    free_string(dirty_value);
}

unsigned aio_field_particle::illuminate(aio_schemable *schemable)
{
    //TODO: Make put for schemable:
    //Prepare:
    if (!this->field->type) {
        this->field->type = new str_hook(AUTO);
    }
    schemable->fields->add(this->field);
    schemable->instructions->add(this->task);
    this->field = new aio_field();
    this->task = new aio_assign_task();
    return this->token_holder->end;
}