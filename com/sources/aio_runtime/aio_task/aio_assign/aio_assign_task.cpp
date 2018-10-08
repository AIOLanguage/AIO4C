//runtime:
//#include <aio_runtime/aio_task/aio_task.cpp>
#include <aio_runtime/aio_task/aio_assign/aio_assign_task.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

aio_assign_task::aio_assign_task()
{
    this->name = nullptr;
    this->value = nullptr;
}

aio_assign_task::~aio_assign_task()
{
    delete this->name;
    delete this->value;
}

void aio_assign_task::perform(aio_ray *ray)
{}

void aio_assign_task::set_name(str_hook *name)
{
    this->name = name;
}

void aio_assign_task::set_value(char *value)
{
    this->value = value;
}

const str_hook *aio_assign_task::get_name() const
{
    return this->name;
}

const char *aio_assign_task::get_value() const
{
    return this->value;
}