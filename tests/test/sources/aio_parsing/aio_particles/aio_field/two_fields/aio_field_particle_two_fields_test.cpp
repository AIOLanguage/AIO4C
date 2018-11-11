//lang:
#include <aio_lang/aio_types/aio_types.h>
#include <aio_lang/aio_field/aio_field.h>
//runtime:
#include <aio_runtime/aio_task/aio_assign/aio_assign_task.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <lib4aio_cpp_headers/utils/string_utils/common.h>

aio_field *create_field_1_for_aio_two_fields_test()
{
    aio_field *field = new aio_field();
    field->is_const = false;
    field->name = new str_hook("hello");
    field->type = new str_hook(STRING);
    field->is_array = false;
    field->is_static = false;
    field->visibility_type = AIO_VISIBILITY_UNDEFINED;
    return field;
}

aio_field *create_field_2_for_aio_two_fields_test()
{
    aio_field *field = new aio_field();
    field->is_const = true;
    field->name = new str_hook("bye");
    field->type = new str_hook(STRING);
    field->is_array = true;
    field->is_static = false;
    field->visibility_type = AIO_VISIBILITY_PRIVATE;
    return field;
}


aio_assign_task *create_task_1_for_aio_two_fields_test()
{
    aio_assign_task *task = new aio_assign_task();
    task->set_name(new str_hook("hello"));
    task->set_value(new_string("'Hello, AIO!'"));
    return task;
}

aio_assign_task *create_task_2_for_aio_two_fields_test()
{
    aio_assign_task *task = new aio_assign_task();
    task->set_name(new str_hook("bye"));
    task->set_value(new_string("'Bye, AIO'"));
    return task;
}