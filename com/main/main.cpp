//core:
#include <aio_core/aio_core.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>

/**
 * 태그들.
 */

#define AIO_ERROR_TAG "AIO_ERROR"

#define AIO_INFO_TAG "AIO_INFO"

#define AIO_DEBUG

#define AIO_TEST

#ifdef AIO_DEBUG

//lib4aio:
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>

#endif

#ifdef AIO_TEST

//google test:
#include <gtest/gtest.h>
#include <gmock/gmock.h>

//lib4aio:
#include <lib4aio_cpp_headers/utils/color_utils/color_utils.h>

using namespace testing;

#endif

/**
 * 비즈니스 로직.
 */

#define BUILD_DIR_PATH_INDEX 1

//<build dir path> <exe file path> <function name> <args>

int main(int argc, char *argv[])
{
#ifdef AIO_TEST
    InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    log_info(AIO_INFO_TAG, CYAN "TESTING IS COMPLETE!" RESET);
#else
    const bool has_program_args = argc > 1;
    if (has_program_args) {
        aio_core::create()
                ->configure()
                ->inflate(argv[BUILD_DIR_PATH_INDEX])
                ->invoke(argc, argv)
                ->finish();
    } else {
        throw_error_with_tag(AIO_ERROR_TAG, "'*.aio' 에 경로를 예상했습니다 (Expected path to *.aio)");
    }
#endif
    return 0;
}