//native:
#include <cctype>
#include <typeinfo>
//lang:
#include <aio_lang/aio_space/aio_space.h>
#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_types/aio_types.h>
#include <aio_lang/aio_schemable/aio_schemable.h>
#include <aio_lang/aio_modifiers/aio_modifiers.h>
#include <aio_lang/aio_schemable/aio_schemable.cpp>
//parsing:
#include <aio_parsing/aio_particles/aio_field/aio_field_particle.h>
//runtime:
#include <aio_runtime/aio_task/aio_assign/aio_assign_task.h>
#include <aio_runtime/aio_task/aio_assign/aio_assign_task.cpp>
//lib4aio:
#include <lib4aio_cpp_headers/utils/string_utils/common.h>
#include <lib4aio_cpp_headers/utils/char_utils/char_utils.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

/**
 * 태그들.
 */

#define AIO_FIELD_PARTICLE_DEBUG

#define AIO_FIELD_PARTICLE_INFO_TAG "AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_INFO"

#define AIO_FIELD_PARTICLE_ERROR_TAG "AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_ERROR"

#ifdef AIO_FIELD_PARTICLE_DEBUG

#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>
#include <aio_lang/aio_space/aio_space.h>

#endif

/**
 * 비즈니스 러직.
 */

using namespace lib4aio;

template<typename T>
aio_field_particle<T>::aio_field_particle(array_list<str_hook> *type_list_ptr, array_list<aio_field> *field_list_ptr)
{
    this->type_list_ptr = type_list_ptr;
    this->field_list_ptr = field_list_ptr;
    this->monitor_mode = AIO_MONITOR_MODIFIER;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    this->whitespace_counter = 0;
}

template<typename T>
aio_field_particle<T>::~aio_field_particle()
{
    this->reset();
}

template<typename T>
void aio_field_particle<T>::reset()
{
    delete this->assign_task;
    delete this->field;
}

template<typename T>
const aio_particle_signal aio_field_particle<T>::handle_symbol(const unsigned position)
{
    const char symbol = this->string[position];
    switch (this->monitor_mode) {
        case AIO_MONITOR_MODIFIER:
            this->monitor_field_modifier(symbol, position);
            break;
        case AIO_MONITOR_NAME:
            this->monitor_field_name(symbol, position);
            break;
        case AIO_MONITOR_TYPE:
            this->monitor_field_type(symbol, position);
            break;
        case AIO_MONITOR_EQUAL_SIGN:
            this->monitor_equal_sign(symbol, position);
            break;
        case AIO_MONITOR_VALUE:
            this->monitor_value(symbol, position);
            break;
    }
    return this->signal;
}

template<typename T>
void aio_field_particle<T>::monitor_field_modifier(const char symbol, const unsigned position)
{
    //기호를 확인하다:
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    const bool is_token_scan_started = !is_whitespace_cond && this->trigger_mode == AIO_TRIGGER_MODE_PASSIVE;
    if (is_token_scan_started) {
        this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
        this->token_holder->start = position;
    }
    const bool is_token_scan_finished = is_whitespace_cond && this->trigger_mode == AIO_TRIGGER_MODE_ACTIVE;
    if (is_token_scan_finished) {
        this->token_holder->end = position;
        const bool is_constant_modifier = is_aio_constant_modifier(this->token_holder);
        const bool is_variable_modifier = is_aio_variable_modifier(this->token_holder);
        if (is_constant_modifier || is_variable_modifier) {
#ifdef AIO_FIELD_PARTICLE_DEBUG
            log_info_str_hook(AIO_FIELD_PARTICLE_INFO_TAG, "Found modifier:", this->token_holder);
#endif
            //Create field:
            this->field = new aio_field();
            this->field->is_const = is_constant_modifier;
            //Create assign instruction:
            this->assign_task = new aio_assign_task<T>();
            //Prepare to the next state:
            this->monitor_mode = AIO_MONITOR_NAME;
            this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
            this->trigger_mode = AIO_TRIGGER_MODE_UNDEFINED;
        } else {
            //Else this is variable name:
            const bool is_valid_name = this->token_holder->is_word() && is_successful_aio_name(this->token_holder);
            if (is_valid_name) {
                //Check field in list:
                const bool has_field_in_scope = this->field_list_ptr->contains_by(
                        [this](const aio_field *it) -> bool {
                            return it->name->equals_string(this->token_holder);
                        });
                if (has_field_in_scope) {
                    this->assign_task = new aio_assign_task<T>();
                    this->assign_task->set_name(this->token_holder);
                    //Prepare to the next state:
                    this->monitor_mode = AIO_MONITOR_EQUAL_SIGN;
                    this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
                    this->trigger_mode = AIO_TRIGGER_MODE_UNDEFINED;
                    this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
                }
            }
        }
    }
}

template<typename T>
void aio_field_particle<T>::monitor_field_name(const char symbol, const unsigned position)
{
    //기호를 확인하다:
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    const bool is_equal_sign_cond = is_equal_sign(symbol);
    const bool is_token_scan_started = !is_whitespace_cond && this->trigger_mode == AIO_TRIGGER_MODE_PASSIVE;
    if (is_token_scan_started) {
        this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
        this->token_holder->start = position;
    }
    const bool is_token_scan_finished = (is_whitespace_cond || is_equal_sign_cond)
                                        && this->trigger_mode == AIO_TRIGGER_MODE_ACTIVE;
    if (is_token_scan_finished) {
        this->token_holder->end = position;
        const bool is_valid_name = this->token_holder->is_word() && is_successful_aio_name(this->token_holder);
        if (is_valid_name) {
#ifdef AIO_FIELD_PARTICLE_DEBUG
            log_info_str_hook(AIO_FIELD_PARTICLE_INFO_TAG, "Found name:", this->token_holder);
#endif
            //Create field:
            this->field->name = new str_hook(this->token_holder);
            //Fill assign instruction command:
            this->assign_task->set_name(new str_hook(this->token_holder));
            if (is_equal_sign_cond) {
                //Set auto type:
                this->field->type = new str_hook(AUTO);
                this->monitor_mode = AIO_MONITOR_VALUE;
            } else {
                this->monitor_mode = AIO_MONITOR_TYPE;
            }
            //Prepare to the next state:
            this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
            this->trigger_mode = AIO_TRIGGER_MODE_UNDEFINED;
        }
    }
}

#define AIO_LIST_BRACKETS "[]"

#define AIO_LIST_SEMANTICS_SIZE 2

template<typename T>
void aio_field_particle<T>::monitor_field_type(const char symbol, const unsigned position)
{
    //기호를 확인하다:
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    const bool is_equal_sign_cond = is_equal_sign(symbol);
    const bool is_semicolon_cond = is_semicolon(symbol);
    const bool is_token_scan_started = !is_whitespace_cond && this->trigger_mode == AIO_TRIGGER_MODE_PASSIVE;
    if (is_token_scan_started) {
        this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
        this->token_holder->start = position;
    }
    const bool is_token_scan_finished = (is_whitespace_cond || is_equal_sign_cond || is_semicolon_cond)
                                        && this->trigger_mode == AIO_TRIGGER_MODE_ACTIVE;
    if (is_token_scan_finished) {
        this->token_holder->end = position;
        const bool is_valid_type = this->type_list_ptr->contains_by(
                [this](const str_hook *it) -> bool {
                    it->equals_string(this->token_holder);
                });
        if (is_valid_type) {
#ifdef AIO_FIELD_PARTICLE_DEBUG
            log_info_str_hook(AIO_FIELD_PARTICLE_INFO_TAG, "Found type:", this->token_holder);
#endif
            this->field->type = new str_hook(this->token_holder);
            if (this->token_holder->ends_with(AIO_LIST_BRACKETS)) {
                this->field->is_list = true;
                this->field->type->end -= AIO_LIST_SEMANTICS_SIZE;
            } else {
                this->field->is_list = false;
            }
            if (is_equal_sign_cond) {
                this->monitor_mode = AIO_MONITOR_VALUE;
            } else if (is_semicolon_cond) {
                this->assign_task->set_value(new_string(AIO_NULL_VALUE));
                this->signal = AIO_PARTICLE_SIGNAL_IS_READY;
            } else {
                this->monitor_mode = AIO_MONITOR_EQUAL_SIGN;
            }
            //Prepare to the next state:
            this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
            this->trigger_mode = AIO_TRIGGER_MODE_UNDEFINED;
        } else {
            throw_error_with_str_hook(AIO_FIELD_PARTICLE_ERROR_TAG, "Cannot identify field type:", this->token_holder);
        }
    }
}

template<typename T>
void aio_field_particle<T>::monitor_equal_sign(const char symbol, const unsigned position)
{
    //기호를 확인하다:
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    if (!is_whitespace_cond) {
        const bool is_equal_sign_cond = is_equal_sign(symbol);
        if (is_equal_sign_cond) {
            this->trigger_mode = AIO_TRIGGER_MODE_UNDEFINED;
            this->monitor_mode = AIO_MONITOR_VALUE;
            this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
#ifdef AIO_FIELD_PARTICLE_DEBUG
            log_info(AIO_FIELD_PARTICLE_INFO_TAG, "Detected equal sign");
#endif
        } else {
            throw_error_with_tag(AIO_FIELD_PARTICLE_ERROR_TAG, "예상되는 'a' 기호");
        }
    }
}

template<typename T>
void aio_field_particle<T>::monitor_value(const char symbol, const unsigned position)
{
#ifdef AIO_FIELD_PARTICLE_DEBUG
    log_info_char(AIO_FIELD_PARTICLE_INFO_TAG, "C:", symbol);
#endif

    if (is_single_quote(symbol)) {
        this->is_inside_string = !this->is_inside_string;
    }
    if (!this->is_inside_string) {
        switch (this->trigger_mode) {
            case AIO_TRIGGER_MODE_UNDEFINED:
                if (!is_space_or_line_break(symbol)) {
                    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
                    this->token_holder->start = position;
#ifdef AIO_FIELD_PARTICLE_DEBUG
                    log_info(AIO_FIELD_PARTICLE_INFO_TAG, "SET START POSITION");
#endif
                }
                break;
            case AIO_TRIGGER_MODE_PASSIVE:
                this->whitespace_counter = 0;
                if (isalnum(symbol) || is_closing_parenthesis(symbol) || is_single_quote(symbol)) {
                    this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
#ifdef AIO_FIELD_PARTICLE_DEBUG
                    log_info(AIO_FIELD_PARTICLE_INFO_TAG, "DETECTED POSSIBLE BORDER");
#endif
                }
                break;
            case AIO_TRIGGER_MODE_ACTIVE:
                if (is_space_or_line_break(symbol)) {
                    this->whitespace_counter++;
                }
#ifdef AIO_FIELD_PARTICLE_DEBUG
                log_info_int(AIO_FIELD_PARTICLE_INFO_TAG, "COUNTER:", this->whitespace_counter);
                log_info_boolean(AIO_FIELD_PARTICLE_INFO_TAG, "IS BORDER:",
                                 position == this->right_border - 1);
#endif
                const bool is_end_of_holder = position == this->right_border - 1;
                if ((isalpha(symbol) && this->whitespace_counter > 0)
                    || is_closing_brace(symbol)
                    || is_end_of_holder) {
                    //Subtract whitespace count to move right border:
                    if (is_end_of_holder) {
                        this->token_holder->end = this->right_border;
                    } else {
                        this->token_holder->end = position - this->whitespace_counter;
                    }
#ifdef AIO_FIELD_PARTICLE_DEBUG
                    log_info_str_hook(AIO_FIELD_PARTICLE_INFO_TAG, "Detected value:",
                                      this->token_holder);
#endif
                    //값을 놓다:
                    char *dirty_value = this->token_holder->to_string();
                    char *clean_value = squeeze_string_for_expression(dirty_value);
                    this->assign_task->set_value(clean_value);
                    //위빙 준비:
                    this->token_holder->start = this->token_holder->end;
                    this->signal = AIO_PARTICLE_SIGNAL_IS_READY;
                    //----------------------------------------------------------------------------------------------------------
                    //찌거기 수집기:
                    free_string(dirty_value);
                }
                break;
        }
    }
}

template<typename T>
unsigned aio_field_particle<T>::illuminate(T *container)
{
    aio_space *space = dynamic_cast<aio_space *>(container);
    if (space) {
        //Set field:
        space->field_definition_list->add(this->field);
        this->field = nullptr;
        //Set assign task:
        space->get_instructions()->add((aio_task<aio_space> *) this->assign_task);
        this->assign_task = nullptr;
    } else {
        throw_error_with_details(
                AIO_FIELD_PARTICLE_INFO_TAG,
                "Required aio_space type instead:",
                typeid(container).name()
        );
    }
    return this->token_holder->end;
}