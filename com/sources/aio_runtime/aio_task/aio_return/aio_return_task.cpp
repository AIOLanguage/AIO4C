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

bool aio_return_task::operator==(const aio_task *task) const
{
    const aio_return_task *other = dynamic_cast<const aio_return_task *>(task);
    if (other) {
        if ((!this->value && other->value) || (this->value && !other->value)) {
            return false;
        }
        return strcmp(this->value, other->value) == 0;
    } else {
        return false;
    }
}