#include <lang/aio_function/aio_bundle/aio_bundle.h>
#include <lib/utils/boolean_utils/boolean_utils.h>
#include <fcntl.h>
#include <lib/utils/log_utils/log_utils.h>
#include <lib/utils/string_utils/string_utils.h>
#include <lib/utils/str_hook/str_hook.h>
#include <lang/aio_function/aio_function.h>
#include <lib/utils/str_hook/str_hook_utils/str_hook_utils.h>
#include <lib/utils/collections/lists/string_list.h>
#include <lang/aio_core/aio_core.h>
#include <lang/aio_context/aio_context.h>

#define AIO_TAG "AIO"

#define AIO_DEVELOPMENT

static aio_bundle *make_bundle(const int argc, char *argv[])
{
    //Define function args index:
    static const unsigned START_FUNCTION_ARG_INDEX = 3;
    aio_value_list *arguments = new_aio_value_list();
    //Prepare input arguments:
    const_boolean has_function_arguments = argc > START_FUNCTION_ARG_INDEX;
    if (has_function_arguments) {
        for (int i = START_FUNCTION_ARG_INDEX; i < argc; ++i) {
            aio_value *argument = new_aio_value_by_string(argv[i]);
            add_aio_value_in_list(arguments, argument);
        }
    }
    return new_aio_bundle(arguments);
}

static void print_result(const aio_value_list *result_list)
{
    const size_t result_list_size = result_list->size;
    const aio_value_array result_array = result_list->values;
    for (int j = 0; j < result_list_size; ++j) {
        const aio_value *result = result_array[j];
        log_info_aio_value(AIO_TAG, "<Result>:", result);
    }
}

static void make_aio(const int argc, char *argv[])
{
    //Define indexes:
    static const unsigned FILE_PATH_INDEX = 1;
    static const unsigned FUNCTION_NAME_INDEX = 2;
    //Init args:
    const_string file_path = argv[FILE_PATH_INDEX];
    const_string function_name = argv[FUNCTION_NAME_INDEX];
    aio_bundle *input_bundle = make_bundle(argc, argv);
    //Init core:
    inflate_aio_core();
    //Prepare to invoke function:
    str_hook *test_hook = new_str_hook_by_string(function_name);
    aio_value_list *result_list = invoke_static_function_in_context(test_hook, input_bundle);
    //Print result:
    print_result(result_list);
    //Close AIO:
    deflate_aio_core();
    //----------------------------------------------------------------------------------------------------------------—
    //찌꺼기 수집기 (Garbage collector):
    free_str_hook(test_hook);
    free_aio_bundle(input_bundle);
    free_aio_value_list(result_list);
}

#ifdef AIO_DEVELOPMENT

#define AIO_DEVELOPMENT_DEBUG

#define AIO_DEVELOPMENT_TAG "AIO_DEVELOPMENT"

#ifdef AIO_DEVELOPMENT_DEBUG

#endif

static string_list *create_test_arguments()
{
    string_list *args = new_string_list();
    add_string_in_list(args, "");
    add_string_in_list(args, "../aioPrograms/tests/complexTests/variables/Trivial.aio");
    add_string_in_list(args, "countSqrHypotenuse");
    add_string_in_list(args, "3");
    add_string_in_list(args, "'4'");
    return args;
}

static void make_test()
{
    //Prepare test:
    string_list *arg_list = create_test_arguments();
    const size_t size = arg_list->size;
    const_string_array args = arg_list->strings;
    //Make AIO:
    make_aio(size, args);
    //----------------------------------------------------------------------------------------------------------------—
    //찌꺼기 수집기 (Garbage collector):
    free_string_list(arg_list);
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