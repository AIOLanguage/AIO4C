#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "../headers/lang/aio_core/aio_core.h"
#include "../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"

#define AIO_DEVELOPMENT

#ifdef AIO_DEVELOPMENT

aio_bundle *create_test_bundle() {
    aio_value_list *input_value_list = new_aio_value_list();
    add_aio_value_in_list(input_value_list, new_aio_int_value(2));
    add_aio_value_in_list(input_value_list, new_aio_int_value(0));
    add_aio_value_in_list(input_value_list, new_aio_double_value(7.9));
    add_aio_value_in_list(input_value_list, new_aio_string_value("'AIO_DEVELOPMENT'"));
    add_aio_value_in_list(input_value_list, new_aio_boolean_value(TRUE));
    return new_aio_bundle(input_value_list);
}

void make_test() {
#ifdef AIO_PROJECT_MEMORY_MANAGER
    inflate_aio_project_controller();
#endif
    inflate_aio_core();
    const_string aio_test_file_path = "../aio_programs/test.aio";
    const_aio_context *context = inflate_aio_context_and_put_in_core(aio_test_file_path);
    //Prepare to invoke function:
    const_string test_function_name = "makeTest";
    const_str_hook *test_hook = new_str_hook_by_string(test_function_name);
    aio_bundle *bundle = create_test_bundle();
    invoke_static_function_in_context(context, test_hook, bundle);
    //찌꺼기 수집기 (Garbage collector):
    free((void *) aio_test_file_path);
    free_const_str_hook(test_hook);
    free((void *) test_function_name);
#ifdef AIO_PROJECT_MEMORY_MANAGER
    free_aio_project_controller();
#endif
}

#endif

int main() {
#ifdef AIO_DEVELOPMENT
    make_test();
#endif
    return 0;
}