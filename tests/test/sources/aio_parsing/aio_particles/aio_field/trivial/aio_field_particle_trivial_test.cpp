//lang:
#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_types/aio_types.h>
//runtime:
#include <aio_runtime/aio_task/aio_task.h>
//lib4aio:
#include <aio_runtime/aio_task/aio_assign/aio_assign_task.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <lib4aio_cpp_headers/utils/string_utils/common.h>

aio_field *create_field_for_aio_field_trivial_test()
{
    aio_field *expected_field = new aio_field();
    expected_field->name = new str_hook("x");
    expected_field->visibility_type = AIO_VISIBILITY_UNDEFINED;
    expected_field->is_static = false;
    expected_field->is_const = true;
    expected_field->is_array = false;
    expected_field->type = new str_hook(AUTO);
    return expected_field;
}

aio_assign_task * create_task_for_aio_field_trivial_test()
{
    aio_assign_task *task = new aio_assign_task();
    task->set_name(new str_hook("x"));
    task->set_value(new_string("3"));
    return task;
}