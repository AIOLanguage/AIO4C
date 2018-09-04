#include <aio_utils/aio_bundle/aio_bundle.h>
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>

#define FILE_PATH_INDEX 1

#define FUNCTION_NAME_INDEX 2

#define START_FUNCTION_ARG_INDEX 3

#define AIO_TAG "AIO"

#define AIO_DEVELOPMENT

static aio_bundle *create_bundle(const int argc, char **argv)
{
    //Build bundle:
    auto file_path = new_str_hook_by_string(argv[FILE_PATH_INDEX]);
    auto function_name = new_str_hook_by_string(argv[FUNCTION_NAME_INDEX]);
    auto arguments = new_aio_value_list();
    //Prepare input arguments:
    auto has_function_arguments = argc > START_FUNCTION_ARG_INDEX;
    if (has_function_arguments) {
        for (int i = START_FUNCTION_ARG_INDEX; i < argc; ++i) {
            var argument = new_aio_value_by_string(argv[i]);
            add_aio_value_in_list(arguments, argument);
        }
    }
    return new_aio_bundle(file_path, function_name, arguments);
}

static void make_aio(const int argc, char *argv[])
{
    //인수들을 초기화하다:
    auto input_bundle = create_bundle(argc, argv);
    //Run AIO:
//    auto result_list = inflate_aio_core(input_bundle);
    //Print result:
//    print_result(result_list);
//    //----------------------------------------------------------------------------------------------------------------—
//    //찌꺼기 수집기 (Garbage collector):
//    free_aio_bundle(input_bundle);
//    free_aio_value_list(result_list);
}

#ifdef AIO_DEVELOPMENT

#define AIO_DEVELOPMENT_DEBUG

#define AIO_DEVELOPMENT_TAG "AIO_DEVELOPMENT"

#ifdef AIO_DEVELOPMENT_DEBUG

#endif

static void make_test()
{
    //테스트를 준비하다:
    char *args[1024] = {
            const_cast<char *>(""),
            const_cast<char *>("../aioPrograms/tests/complexTests/variables/Trivial.aio"),
            const_cast<char *>("countSqrHypotenuse"),
            const_cast<char *>("3"),
            const_cast<char *>("'4'")
    };
    auto size = 5;
    //아이어 만들다:
    make_aio(size, args);
}

#endif

int main(int argc, char *argv[])
{
#ifdef AIO_DEVELOPMENT
    make_test();
#else
    make_aio(argc, argv);
#endif
    return 0;
}