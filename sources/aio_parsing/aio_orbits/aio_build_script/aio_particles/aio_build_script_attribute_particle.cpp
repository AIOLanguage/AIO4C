#include <cctype>
#include <aio_core/aio_build_script.h>
#include <aio_parsing/aio_orbits/aio_build_script/aio_particles/aio_build_script_attribute_particle.h>
#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>
#include <lib4aio_cpp_sources/aio_orbit/aio_particle/aio_particle.cpp>
#include <lib4aio_cpp_headers/utils/string_utils/common.h>
#include <lib4aio_cpp_headers/utils/char_utils/char_utils.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/point_watcher/point_watcher.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

#define AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_DEBUG

#define AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_INFO_TAG "AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_INFO"

#define AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_ERROR_TAG "AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_ERROR"

using namespace lib4aio;

aio_build_script_attribute_particle::aio_build_script_attribute_particle()
{
    this->monitor_mode = AIO_MONITOR_ATTRIBUTE;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    this->whitespace_counter = 0;
}

aio_build_script_attribute_particle::~aio_build_script_attribute_particle()
{
    this->reset();
}

void aio_build_script_attribute_particle::reset()
{
    char *old_attribute = this->config_materials.attribute;
    char *old_value = this->config_materials.value;
    this->config_materials.attribute = nullptr;
    this->config_materials.value = nullptr;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기:
    free_string(old_attribute);
    free_string(old_value);
}

const aio_particle_signal aio_build_script_attribute_particle::handle_symbol(const unsigned position)
{
    const char symbol = this->string[position];
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    if (this->trigger_mode == AIO_TRIGGER_MODE_PASSIVE && !is_whitespace_cond) {
        this->token_holder->start = position;
        this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
    }
    if (this->trigger_mode == AIO_TRIGGER_MODE_ACTIVE) {
        if (this->monitor_mode == AIO_MONITOR_ATTRIBUTE) {
            handle_attribute_data(symbol, position);
        }
        if (this->monitor_mode == AIO_MONITOR_EQUAL_SIGN) {
            handle_equal_sign_data(symbol, position);
            return this->signal;
        }
        if (this->monitor_mode == AIO_MONITOR_VALUE) {
            handle_value_data(symbol, position);
        }
    }
    return this->signal;
}

void aio_build_script_attribute_particle::handle_attribute_data(const char symbol, const unsigned position)
{
    //기호를 확인하다:
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    const bool is_equal_sign_cond = is_equal_sign(symbol);
    const bool is_token_scan_finished = (is_whitespace_cond || is_equal_sign_cond) && !this->is_inside_string;
    if (is_token_scan_finished) {
        this->token_holder->end = position;
        const bool is_valid_attribute_name = this->token_holder->is_word();
        if (is_valid_attribute_name) {
            this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
            //속성을 만들다:
            this->config_materials.attribute = token_holder->to_string();
            if (is_equal_sign_cond) {
                this->monitor_mode = AIO_MONITOR_VALUE;
                this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
            } else {
                this->monitor_mode = AIO_MONITOR_EQUAL_SIGN;
            }
        } else {
            throw_error_with_str_hook(
                    AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_ERROR_TAG,
                    "속성 이름이 잘못되었습니다!",
                    this->token_holder
            );
        }
    }
}

void aio_build_script_attribute_particle::handle_equal_sign_data(const char symbol, const unsigned position)
{
    //기호를 확인하다:
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    if (!is_whitespace_cond) {
        const bool is_equal_sign_cond = is_equal_sign(symbol);
        if (is_equal_sign_cond) {
            this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
            this->monitor_mode = AIO_MONITOR_VALUE;
            this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
            this->token_holder->start = position + 1;
        } else {
            throw_error_with_tag(AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_ERROR_TAG, "예상되는 'a' 기호");
        }
    }
}

void aio_build_script_attribute_particle::handle_value_data(const char symbol, const unsigned position)
{
    const bool is_quote_cond = is_single_quote(symbol);
    if (is_quote_cond) {
        this->is_inside_string = !this->is_inside_string;
    }
    const bool is_beyond_string_context = this->is_inside_string;
    if (!is_beyond_string_context) {
        //기호를 확인하다:
        const bool is_whitespace_cond = is_space_or_line_break(symbol);
        const bool is_letter_cond = isalpha(symbol);
        const bool is_close_brace_cond = is_closing_brace(symbol);
        const bool is_possible_bound
                = isalnum(symbol) || is_closing_parenthesis(symbol) || is_quote_cond;
        //Monitor whitespaces in the expression:
        const bool is_whitespace_in_expression = is_whitespace_cond && this->trigger_mode == AIO_TRIGGER_MODE_ACTIVE;
        if (is_whitespace_in_expression) {
            this->whitespace_counter++;
            return;
        }
        //Monitor end of expression:
        const bool is_end_of_expression
                = ((is_letter_cond && this->token_holder->end > 0) || is_close_brace_cond) &&
                  this->trigger_mode == AIO_TRIGGER_MODE_ACTIVE;
        if (is_end_of_expression) {
            //Subtract whitespace count to move right border:
            this->token_holder->end = position - this->whitespace_counter;
            //값을 놓다:
            char *dirty_value = this->token_holder->to_string();
            char *clean_value = squeeze_string_for_expression(dirty_value);
            this->config_materials.value = clean_value;
            //위빙 준비:
            this->token_holder->start = token_holder->end;
            this->signal = AIO_PARTICLE_SIGNAL_IS_READY;
            //----------------------------------------------------------------------------------------------------------
            //찌거기 수집기:
            free_string(dirty_value);
            //----------------------------------------------------------------------------------------------------------
            return;
        }
            //Reset trigger: this is not end of the expression!
        else {
            this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
            this->whitespace_counter = 0;
            if (is_possible_bound) {
                this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
                return;
            }
        }
    }
}

unsigned aio_build_script_attribute_particle::illuminate(aio_build_script_space *space)
{
    const char *value = this->config_materials.value;
    const char *build_script_keyword = this->config_materials.attribute;
    if (are_equal_strings(build_script_keyword, AIO_BUILD_SCRIPT_MAIN_KEYWORD)) {
        space->main_path = value;
    } else {
        throw_error_with_details(
                AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_ERROR_TAG,
                "Such keyword is not supported!",
                build_script_keyword
        );
    }
    this->config_materials.value = nullptr;
    return this->token_holder->end;
}