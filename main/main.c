
#include <aio_core/aio_core.h>
#include <aio_tools/aio_common_tools/aio_utils/aio_bundle/aio_bundle.h>
#include <lib/utils/type_utils/type.utils.h>
#include <lib/utils/str_hook/str_hook_utils/str_hook_utils.h>
#include <aio_tools/aio_common_tools/aio_utils/aio_value/aio_value.h>
#include <lib/utils/collections/lists/string_list.h>

#define AIO_TAG "AIO"

#define AIO_DEVELOPMENT

static aio_bundle *create_bundle(const int argc, char **argv)
{
    //Define indexes:
    static val FILE_PATH_INDEX = 1;
    static val FUNCTION_NAME_INDEX = 2;
    //Define function args position:
    static val START_FUNCTION_ARG_INDEX = 3;
    //Build bundle:
    var file_path = new_str_hook_by_string(argv[FILE_PATH_INDEX]);
    var function_name = new_str_hook_by_string(argv[FUNCTION_NAME_INDEX]);
    var arguments = new_aio_value_list();
    //Prepare input arguments:
    val has_function_arguments = argc > START_FUNCTION_ARG_INDEX;
    if (has_function_arguments) {
        for (int i = START_FUNCTION_ARG_INDEX; i < argc; ++i) {
            var argument = new_aio_value_by_string(argv[i]);
            add_aio_value_in_list(arguments, argument);
        }
    }
    return new_aio_bundle(file_path, function_name, arguments);
}

static void print_result(const aio_value_list *result_list)
{
    val result_list_size = result_list->size;
    var result_array = result_list->values;
    for (int j = 0; j < result_list_size; ++j) {
        val result = result_array[j];
        log_info_aio_value(AIO_TAG, "<Result>:", result);
    }
}

static void make_aio(const int argc, char *argv[])
{
    //Init args:
    var input_bundle = create_bundle(argc, argv);
    //Run AIO:
    var result_list = inflate_aio_core(input_bundle);
    //Print result:
    print_result(result_list);
    //----------------------------------------------------------------------------------------------------------------—
    //찌꺼기 수집기 (Garbage collector):
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
    var args = new_string_list();
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
    var arg_list = create_test_arguments();
    val size = arg_list->size;
    var args = arg_list->strings;
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