//native:
#include <cstring>
#include <typeinfo>
//runtime:
#include <aio_runtime/aio_task/aio_return/aio_return_task.h>
#include <cstdio>

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

bool aio_return_task::equals(const aio_task *task) const
{
    printf("DDD: \n");
    aio_return_task *other = (aio_return_task *) task;
    if ((!this->value && other->value) || (this->value && !other->value)) {
        return false;
    }
    printf("EEEE: \n");
    printf("MY: %s\n", this->value);
    printf("OTHER: %s\n", other->value);
    return strcmp(this->value, other->value) == 0;
}