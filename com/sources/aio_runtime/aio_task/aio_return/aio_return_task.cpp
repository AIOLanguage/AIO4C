
#include <aio_runtime/aio_task/aio_return/aio_return_task.h>

aio_return_task::aio_return_task()
{}

aio_return_task::~aio_return_task()
{}

void aio_return_task::perform(aio_ray *ray)
{}

char *aio_return_task::get_value()
{
    return this->value;
}

void aio_return_task::set_value(char *value)
{
    this->value = value;
}