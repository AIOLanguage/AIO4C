//#define AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_DEBUG

#define AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_INFO_TAG "AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_INFO"

#define AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_ERROR_TAG "AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_ERROR"

#ifdef AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_DEBUG

#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>

#endif

using namespace lib4aio;

aio_build_script_attribute_particle::aio_field_particle()
{
    this->monitor_mode = AIO_MONITOR_ATTRIBUTE;
    this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
    this->whitespace_counter = 0;
}

aio_build_script_attribute_particle::~aio_field_particle()
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
    switch (this->monitor_mode) {
        case AIO_MONITOR_ATTRIBUTE:
            handle_attribute_data(symbol, position);
            break;
        case AIO_MONITOR_EQUAL_SIGN:
            handle_equal_sign_data(symbol, position);
            break;
        case AIO_MONITOR_VALUE:
            handle_value_data(symbol, position);
    }
    return this->signal;
}

void aio_build_script_attribute_particle::handle_attribute_data(const char symbol, const unsigned position)
{
    //기호를 확인하다:
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    const bool is_equal_sign_cond = is_equal_sign(symbol);
    const bool is_token_scan_finished = (is_whitespace_cond || is_equal_sign_cond) && !this->is_inside_string;
    if (!is_whitespace_cond && this->trigger_mode == AIO_TRIGGER_MODE_PASSIVE) {
        this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
        this->token_holder->start = position;
    }
    if (is_token_scan_finished) {
        this->token_holder->end = position;
        const bool is_valid_attribute_name = this->token_holder->is_word();
        if (is_valid_attribute_name) {
            //속성을 만들다:
#ifdef AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_DEBUG
            log_info_str_hook(AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_INFO_TAG, "Found attribute:", this->token_holder);
#endif
            this->config_materials.attribute = token_holder->to_string();
            if (is_equal_sign_cond) {
                this->monitor_mode = AIO_MONITOR_VALUE;
                this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
                this->trigger_mode = AIO_TRIGGER_MODE_UNDEFINED;
            } else {
                this->trigger_mode = AIO_TRIGGER_MODE_PASSIVE;
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
            this->trigger_mode = AIO_TRIGGER_MODE_UNDEFINED;
            this->monitor_mode = AIO_MONITOR_VALUE;
            this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
#ifdef AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_DEBUG
            log_info(AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_INFO_TAG, "Detected equal sign");
#endif
        } else {
            throw_error_with_tag(AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_ERROR_TAG, "예상되는 'a' 기호");
        }
    }
}

void aio_build_script_attribute_particle::handle_value_data(const char symbol, const unsigned position)
{
#ifdef AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_DEBUG
    log_info_char(AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_INFO_TAG, "C:", symbol);
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
#ifdef AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_DEBUG
                    log_info(AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_INFO_TAG, "SET START POSITION");
#endif
                }
                break;
            case AIO_TRIGGER_MODE_PASSIVE:
                this->whitespace_counter = 0;
                if (isalnum(symbol) || is_closing_parenthesis(symbol) || is_single_quote(symbol)) {
                    this->trigger_mode = AIO_TRIGGER_MODE_ACTIVE;
#ifdef AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_DEBUG
                    log_info(AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_INFO_TAG, "DETECTED POSSIBLE BORDER");
#endif
                }
                break;
            case AIO_TRIGGER_MODE_ACTIVE:
                if (is_space_or_line_break(symbol)) {
                    this->whitespace_counter++;
                }
#ifdef AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_DEBUG
            log_info_int(AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_INFO_TAG, "COUNTER:", this->whitespace_counter);
                log_info_boolean(AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_INFO_TAG, "IS BORDER:",
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
#ifdef AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_DEBUG
                    log_info_str_hook(AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_INFO_TAG, "Detected value:",
                                      this->token_holder);
#endif
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
                }
                break;
        }
    }
}

unsigned aio_build_script_attribute_particle::illuminate(aio_build_script *space)
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
#ifdef AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_DEBUG
    log_info(AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_INFO_TAG, "ILLUMINATION IS COMPLETE");
#endif
    return this->token_holder->end;
}