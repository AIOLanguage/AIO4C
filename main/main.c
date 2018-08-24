
#include <stdlib.h>
#include "../headers/lang/aio_core/aio_core.h"
#include "../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"
#include "../headers/lang/aio_type/aio_type.h"
#include "../headers/lang/aio_function/aio_function.h"


#define AIO_DEVELOPMENT

#ifdef AIO_DEVELOPMENT

#define AIO_DEVELOPMENT_DEBUG

#define AIO_DEVELOPMENT_TAG "AIO_DEVELOPMENT"

#ifdef AIO_DEVELOPMENT_DEBUG

#include "../headers/lib/utils/log_utils/log_utils.h"

#endif

aio_bundle *create_test_bundle()
{
    aio_value_list *input_value_list = new_aio_value_list();
    add_aio_value_in_list(input_value_list, new_aio_int_value(2));
    add_aio_value_in_list(input_value_list, new_aio_double_value(1.25));
    add_aio_value_in_list(input_value_list, new_aio_int_value(7));
    add_aio_value_in_list(input_value_list, new_aio_string_value("AIO_DEVELOPMENT"));
    add_aio_value_in_list(input_value_list, new_aio_string_value("tru"));
    return new_aio_bundle(input_value_list);
}

void make_test()
{
#ifdef AIO_PROJECT_MEMORY_MANAGER
    inflate_aio_project_controller();
#endif
#ifdef AIO_DEVELOPMENT_DEBUG
    log_info(AIO_DEVELOPMENT_TAG, "start to inflate AIO core...");
#endif
    inflate_aio_core();
    const_string aio_test_file_path = "../aio_programs/test.aio";
    const_aio_context *context = inflate_aio_context_and_put_in_core(aio_test_file_path);
#ifdef AIO_DEVELOPMENT_DEBUG
    log_info(AIO_DEVELOPMENT_TAG, "AIO core inflating is complete!");
#endif
    //Prepare to invoke function:
    const_string test_function_name = "makeTest";
    const_str_hook *test_hook = new_str_hook_by_string(test_function_name);
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
        const_str_hook *type = input_value->type;
        if (is_hook_equals_str(type, INTEGER)) {
            log_info_int(AIO_DEVELOPMENT_TAG, "Value:", input_value->get.int_acc);
        }
        if (is_hook_equals_str(type, DOUBLE)) {
            log_info_double(AIO_DEVELOPMENT_TAG, "Value:", input_value->get.double_acc);
        }
        if (is_hook_equals_str(type, STRING)) {
            log_info_string(AIO_DEVELOPMENT_TAG, "Value:", input_value->get.string_acc);
        }
        if (is_hook_equals_str(type, BOOLEAN)) {
            log_info_boolean(AIO_DEVELOPMENT_TAG, "Value:", input_value->get.boolean_acc);
        }
    }
#endif
//    exit(1);
    invoke_static_function_in_context(context, test_hook, bundle);
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