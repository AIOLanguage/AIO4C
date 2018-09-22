#include <cctype>
#include <aio_parsing/aio_orbits/aio_build_script/aio_particles/aio_build_script_attribute_particle.h>
#include <lib4aio_cpp_headers/utils/string_utils/common.h>
#include <lib4aio_cpp_headers/utils/char_utils/char_utils.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

#define AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_DEBUG

#define AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_INFO_TAG "AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_INFO"

#define AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_ERROR_TAG "AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_ERROR"

using namespace lib4aio;

aio_build_script_attribute_particle::aio_build_script_attribute_particle()
{
    this->process_mode = AIO_SCAN_ATTRIBUTE;
    this->scan_mode = AIO_WAIT_TOKEN;
}

aio_build_script_attribute_particle::~aio_build_script_attribute_particle()
{
    this->reset();
}

const aio_particle_signal aio_build_script_attribute_particle::handle_symbol(const unsigned position)
{
    const char symbol = this->string[position];
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    if (this->scan_mode == AIO_WAIT_TOKEN && !is_whitespace_cond) {
        this->token_holder->start = position;
        this->scan_mode = AIO_READ_TOKEN;
    }
    if (this->scan_mode == AIO_READ_TOKEN) {
        if (this->process_mode == AIO_SCAN_ATTRIBUTE) {
            handle_attribute_data(symbol, position);
        }
        if (this->process_mode == AIO_SCAN_EQUAL_SIGN) {
            handle_equal_sign_data(symbol, position);
            return this->signal;
        }
        if (this->process_mode == AIO_SCAN_VALUE) {
            handle_value_data(symbol, position);
        }
    }
    return this->signal;
}

unsigned aio_build_script_attribute_particle::illuminate(aio_build_script_space *space)
{
    return 0;
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

void aio_build_script_attribute_particle::handle_attribute_data(const char symbol, const unsigned position)
{
    //기호를 확인하다:
    const bool is_whitespace_cond = is_space_or_line_break(symbol);
    const bool is_equal_sign_cond = is_equal_sign(symbol);
    const bool is_token_scan_finished = (is_whitespace_cond || is_equal_sign_cond) && this->is_beyond_string();
    if (is_token_scan_finished) {
        this->token_holder->end = position;
        const bool is_valid_attribute_name = this->token_holder->is_word();
        if (is_valid_attribute_name) {
            this->scan_mode = AIO_WAIT_TOKEN;
            //속성을 만들다:
            this->config_materials.attribute = token_holder->to_string();
            if (is_equal_sign_cond) {
                this->process_mode = AIO_SCAN_VALUE;
                this->signal = AIO_PARTICLE_SIGNAL_DETECTED;
            } else {
                this->process_mode = AIO_SCAN_EQUAL_SIGN;
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

}

void aio_build_script_attribute_particle::handle_value_data(const char symbol, const unsigned position)
{

}
