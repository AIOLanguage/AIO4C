//lang:
#include <aio_lang/aio_types/aio_types.h>
#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_invokable/aio_function/aio_function.h>
//runtime:
#include <aio_runtime/aio_task/aio_return/aio_return_task.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

aio_function *create_function_for_aio_function_trivial_test()
{
    aio_function *expected_function = new aio_function();

    //Create expected args:
    aio_field *arg1 = new aio_field();
    arg1->name = new str_hook("a");
    arg1->type = new str_hook(INTEGER);
    arg1->visibility = aio_visible::AIO_VISIBILITY_LOCAL;
    arg1->is_static = false;
    arg1->is_const = true;
    arg1->is_array = false;

    aio_field *arg2 = new aio_field();
    arg2->name = new str_hook("b");
    arg2->type = new str_hook(INTEGER);
    arg2->visibility = aio_visible::AIO_VISIBILITY_LOCAL;
    arg2->is_static = false;
    arg2->is_const = true;
    arg2->is_array = false;

    array_list<aio_field> *args = new array_list<aio_field>(true);
    args->add(arg1);
    args->add(arg2);

    //Create expected tasks:
    aio_return_task *return_task = new aio_return_task();
    return_task->set_value(const_cast<char *>("a+b"));

    array_list<aio_task> *tasks = new array_list<aio_task>(true);
    tasks->add(return_task);

    //Fill function:
    expected_function->name = new str_hook("sum");
    expected_function->fields = args;
    expected_function->arg_count = 2;
    expected_function->output_type = new str_hook(AUTO);
    expected_function->visibility = aio_visible::AIO_VISIBILITY_UNDEFINED;
    expected_function->is_array_output = false;
    expected_function->instructions = tasks;
    return expected_function;
}