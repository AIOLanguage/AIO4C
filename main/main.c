#include <fcntl.h>
#include <lang/aio_function/aio_bundle/aio_bundle.h>
#include <lang/aio_function/aio_value/aio_value.h>
#include <lang/aio_core/aio_core.h>
#include <lib/utils/str_hook/str_hook_utils/str_hook_utils.h>
#include <lang/aio_function/aio_function.h>
#include <lib/utils/str_hook/str_hook.h>
#include <lang/aio_context/aio_context.h>

#define AIO_DEVELOPMENT

#ifdef AIO_DEVELOPMENT

#define AIO_TEST_PATH "../aioPrograms/tests/complexTests/variables/Trivial.aio"

#define AIO_TEST_FUNCTION "countSqrHypotenuse"

#define AIO_DEVELOPMENT_DEBUG

#define AIO_DEVELOPMENT_TAG "AIO_DEVELOPMENT"

#ifdef AIO_DEVELOPMENT_DEBUG

#include <lib/utils/log_utils/log_utils.h>

#endif

aio_bundle *create_test_bundle()
{
    aio_value_list *input_value_list = new_aio_value_list();
    //Create test args:
    add_aio_value_in_list(input_value_list, new_aio_int_value(3));
    add_aio_value_in_list(input_value_list, new_aio_string_value("4"));
//    add_aio_value_in_list(input_value_list, new_aio_double_value(10.0));
    //Crete bundle:
    return new_aio_bundle(input_value_list);

}

void make_test()
{
#ifdef AIO_PROJECT_MEMORY_MANAGER
    inflate_aio_project_controller();
#endif
#ifdef AIO_DEVELOPMENT_DEBUG
    log_info(AIO_DEVELOPMENT_TAG, "Start to inflate AIO core...");
#endif
    inflate_aio_core();
    const_aio_context *context = inflate_aio_context_and_put_in_core(AIO_TEST_PATH);
#ifdef AIO_DEVELOPMENT_DEBUG
    log_info(AIO_DEVELOPMENT_TAG, "AIO core inflating is complete!");
#endif
    //Prepare to invoke function:
    const_str_hook *test_hook = new_str_hook_by_string(AIO_TEST_FUNCTION);
#ifdef AIO_DEVELOPMENT_DEBUG
    log_info_str_hook(AIO_DEVELOPMENT_TAG, "Prepare to invoke function:", test_hook);
#endif
    aio_bundle *bundle = create_test_bundle();
#ifdef AIO_DEVELOPMENT_DEBUG
    const_aio_value_list *input_list = bundle->input_values;
    const aio_value_array input_value_array = input_list->values;
    const size_t list_size = input_list->size;
    for (int i = 0; i < list_size; ++i) {
        aio_value *input_value = input_value_array[i];
        log_info_aio_value(AIO_DEVELOPMENT_TAG, "Input value:", input_value);
    }
#endif
//    exit(1);
    aio_value_list *result_list = invoke_static_function_in_context(context, test_hook, bundle);
    //==================================================================================================================
    //Print result:
    const size_t result_list_size = result_list->size;
    aio_value_array result_array = result_list->values;
    log_info(AIO_DEVELOPMENT_TAG, "=========================================");
    log_info(AIO_DEVELOPMENT_TAG, "Print result:");
    for (int j = 0; j < result_list_size; ++j) {
        aio_value *result = result_array[j];
        log_info_aio_value(AIO_DEVELOPMENT_TAG, "<Result>:", result);
    }
    //==================================================================================================================
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_const_str_hook(test_hook);
    free_aio_bundle(bundle);
#ifdef AIO_PROJECT_MEMORY_MANAGER
    free_aio_project_controller();
#endif
}

#endif

int main()
{
#ifdef AIO_DEVELOPMENT
    make_test();
#endif
    return 0;
}