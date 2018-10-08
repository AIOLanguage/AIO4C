//native:
#include <cctype>
#include <typeinfo>
//lang:
#include <aio_lang/aio_space/aio_space.h>
#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_types/aio_types.h>
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

#define AIO_FIELD_PARTICLE_ERROR_TAG "AIO_FIELD_PARTICLE_ERROR_TAG"

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
    this->field = nullptr;
    this->task = nullptr;
    this->reset();
}

aio_field_particle::~aio_field_particle()
{
    this->reset();
}

void aio_field_particle::reset()
{
    delete this->task;
    delete this->field;
    this->whitespace_counter = 0;
    this->monitor_mode = AIO_MONITOR_MODIFIER;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    this->signal = AIO_PARTICLE_SIGNAL_UNDEFINED;
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
        case AIO_MONITOR_TYPE:
            this->monitor_field_type(symbol, position);
            break;
        case AIO_MONITOR_EQUAL_SIGN:
            this->monitor_equal_sign(symbol);
            break;
        case AIO_MONITOR_VALUE:
            this->monitor_value(symbol, position);
            break;
    }
    return this->signal;
}

void aio_field_particle::monitor_modifier(const char symbol, const unsigned position)
{
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    switch (this->trigger_mode) {
        case AIO_TRIGGER_MODE_PASSIVE: {
            if (!is_whitespace_cond) {
                this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                this->token_holder->start = position;
            }
        }
            break;
        case AIO_TRIGGER_MODE_ACTIVE: {
            if (is_whitespace_cond) {
                this->token_holder->end = position;
#ifdef AIO_FIELD_PARTICLE_DEBUG
                log_info_str_hook(AIO_FIELD_PARTICLE_INFO_TAG, "Modifier:", this->token_holder);
#endif
                const bool is_constant_modifier = is_aio_constant_modifier(this->token_holder);
                const bool is_variable_modifier = is_aio_variable_modifier(this->token_holder);
                if (is_constant_modifier || is_variable_modifier) {
                    this->field = new aio_field();
                    this->field->is_const = is_constant_modifier;
                    this->task = new aio_assign_task();
                    this->monitor_mode = AIO_MONITOR_NAME;
                    this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
                }
                this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
            }
        }
            break;
        case AIO_TRIGGER_MODE_UNDEFINED:
            throw_error_with_tag(AIO_FIELD_PARTICLE_ERROR_TAG, "Invalid trigger state!");
    }
}

void aio_field_particle::monitor_name(const char symbol, const unsigned position)
{
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    switch (this->trigger_mode) {
        case AIO_TRIGGER_MODE_PASSIVE: {
            if (!is_whitespace_cond) {
                this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                this->token_holder->start = position;
            }
        }
            break;
        case AIO_TRIGGER_MODE_ACTIVE: {
            const bool is_equal_sign_cond = is_equal_sign(symbol);
            if (is_whitespace_cond || is_equal_sign_cond) {
                this->token_holder->end = position;
#ifdef AIO_FIELD_PARTICLE_DEBUG
                log_info_str_hook(AIO_FIELD_PARTICLE_INFO_TAG, "Name:", this->token_holder);
#endif
                this->field->name = new str_hook(this->token_holder);
                this->task->set_name(new str_hook(this->token_holder));
                if (is_equal_sign_cond) {
                    this->field->type = new str_hook(AUTO);
                    this->monitor_mode = AIO_MONITOR_VALUE;
                } else {
                    this->monitor_mode = AIO_MONITOR_TYPE;
                }
                this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
                this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
            }
        }
            break;
        case AIO_TRIGGER_MODE_UNDEFINED:
            throw_error_with_tag(AIO_FIELD_PARTICLE_ERROR_TAG, "Invalid trigger state!");
    }
}

void aio_field_particle::monitor_field_type(const char symbol, const unsigned position)
{
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    const bool is_equal_sign_cond = is_equal_sign(symbol);
    const bool is_semicolon_cond = is_semicolon(symbol);
    switch (this->trigger_mode) {
        case AIO_TRIGGER_MODE_PASSIVE: {
            if (is_equal_sign_cond) {
                this->field->type = new str_hook(AUTO);
                this->trigger_mode = AIO_TRIGGER_MODE_UNDEFINED;
                this->monitor_mode = AIO_MONITOR_VALUE;
                this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
            } else if (!is_whitespace_cond) {
                this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                this->token_holder->start = position;
            }
        }
            break;
        case AIO_TRIGGER_MODE_ACTIVE: {
            if (is_whitespace_cond || is_equal_sign_cond || is_semicolon_cond) {
                this->token_holder->end = position;
#ifdef AIO_FIELD_PARTICLE_DEBUG
                log_info_str_hook(AIO_FIELD_PARTICLE_INFO_TAG, "Type:", this->token_holder);
#endif
                this->field->type = new str_hook(this->token_holder);
                if (is_equal_sign_cond) {
                    this->monitor_mode = AIO_MONITOR_VALUE;
                } else if (is_semicolon_cond) {
                    this->task->set_value(new_string(AIO_NULL_VALUE));
                    this->signal = AIO_PARTICLE_SIGNAL_IS_READY;
                } else {
                    this->monitor_mode = AIO_MONITOR_EQUAL_SIGN;
                }
                this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
                this->trigger_mode = AIO_TRIGGER_MODE_UNDEFINED;
            }
        }
            break;
        case AIO_TRIGGER_MODE_UNDEFINED:
            throw_error_with_tag(AIO_FIELD_PARTICLE_ERROR_TAG, "Invalid trigger state!");
    }
}

void aio_field_particle::monitor_equal_sign(const char symbol)
{
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    if (!is_whitespace_cond) {
        const bool is_equal_sign_cond = is_equal_sign(symbol);
        if (is_equal_sign_cond) {
            this->trigger_mode = AIO_TRIGGER_MODE_UNDEFINED;
            this->monitor_mode = AIO_MONITOR_VALUE;
            this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
        } else {
            throw_error_with_tag(AIO_FIELD_PARTICLE_ERROR_TAG, "예상되는 '=' 기호");
        }
    }
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
    switch (this->trigger_mode) {
        case AIO_TRIGGER_MODE_UNDEFINED: {
            if (!is_whitespace_cond) {
                this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
                this->token_holder->start = position;
                if (is_end_of_holder) {
                    this->construct_value(true, position);
                }
            }
        }
            break;
        case AIO_TRIGGER_MODE_PASSIVE: {
            this->whitespace_counter = 0;
            if ((isalnum(symbol) || is_closing_parenthesis(symbol) || is_single_quote_cond) && in_expression_scope) {
                this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
            }
            if (is_end_of_holder) {
                this->construct_value(true, position);
            }
        }
            break;
        case AIO_TRIGGER_MODE_ACTIVE: {
            if (is_whitespace_cond) {
                this->whitespace_counter++;
            } else if ((((isalpha(symbol) && this->whitespace_counter > 0) || is_closing_brace(symbol))
                        && in_expression_scope) || is_end_of_holder) {
                this->construct_value(is_end_of_holder, position);
            }
        }
    }
}

void aio_field_particle::construct_value(const bool is_end_of_holder, const unsigned position)
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
    //찌거기 수집기:
    free_string(dirty_value);
}

unsigned aio_field_particle::illuminate(aio_schemable *schemable)
{
    schemable->fields->add(this->field);
    schemable->instructions->add(this->task);
    this->field = nullptr;
    this->task = nullptr;
    return this->token_holder->end;
}