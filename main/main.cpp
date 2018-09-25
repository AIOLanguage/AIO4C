//core:
#include <aio_core/aio_core.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>

/**
 * 태그들.
 */

#define AIO_ERROR_TAG "AIO_ERROR"

#define AIO_INFO_TAG "AIO_INFO"

/**
 * 비즈니스 로직.
 */

#define BUILD_SCRIPT_PATH_INDEX 1

int main(int argc, char *argv[])
{
    const bool has_program_args = argc > 1;
    if (has_program_args) {
        aio_core::create()
                ->inflate_aio_config()
                ->inflate_aio_context(argv[BUILD_SCRIPT_PATH_INDEX])
                ->invoke_aio_context(argc, argv)
                ->destroy();
    } else {
        throw_error_with_tag(AIO_ERROR_TAG, "'*.aio_core'에 경로를 예상했습니다 (Expected path to *.aio_core).");
    }
    return 0;
}