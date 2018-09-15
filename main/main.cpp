#include <wchar.h>
#include <clocale>
#include <stdlib.h>
//#include <windows.h>
#include <aio_utils/aio_value/aio_value.h>
#include <aio_utils/aio_bundle/aio_bundle.h>
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <lib4aio_cpp_headers/utils/struct_list/struct_list.h>
#include <aio_core/aio_core.h>

#define FILE_PATH_INDEX 1

#define START_FUNCTION_ARG_INDEX 2

#define ROOT_FUNCTION_NAME "main"

#define AIO_TAG "AIO"

#define AIO_DEVELOPMENT

#ifdef _WINDOWS_

#define UTF_8 65001

#endif

using namespace lib4aio;

static void make_config()
{
#ifdef _WINDOWS_
    SetConsoleOutputCP(UTF_8);
    SetConsoleCP(UTF_8);
    log_info(AIO_TAG, "Windows 구성이 완료되었습니다.");
#endif

}

#ifdef AIO_DEVELOPMENT

#define AIO_DEVELOPMENT_DEBUG

#define AIO_DEVELOPMENT_TAG "AIO_DEVELOPMENT"

#ifdef AIO_DEVELOPMENT_DEBUG

#endif

static void make_test()
{
    //테스트를 준비하기:
    char *args[1024] = {
            //.exe arg:
            const_cast<char *>(""),
            //"build.aio_core" 에게 경로:
            const_cast<char *>("../demo/project1/build.aio_core"),
            //프로그램 인수들:
            const_cast<char *>("a"),
            const_cast<char *>("b"),
            const_cast<char *>("c")
    };
    auto size = 5;
    //아이어 만들기:
    inflate_aio_core(size, args);
}

#endif

int main(int argc, char *argv[])
{
    make_config();
#ifdef AIO_DEVELOPMENT
    make_test();
#else
    inflate_aio_core(argc, argv);
#endif
    return 0;
}