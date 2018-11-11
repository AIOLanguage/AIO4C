//native:
#include <cstring>
#include <typeinfo>
//runtime:
//#include <aio_runtime/aio_task/aio_task.cpp>
#include <aio_runtime/aio_task/aio_assign/aio_assign_task.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>

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

/**
 * Boilerplate.
 */

#define DEBUG

#define TAG "AIO_ASSIGN_TASK"

bool aio_assign_task::equals(const aio_task *task) const
{
#ifdef DEBUG
    log_info(TAG, "START!");
#endif
    aio_assign_task *other = (aio_assign_task *) task;
    if ((!this->name && other->name) || (this->name && !other->name)) {
        return false;
    }
    if (!this->name->equals_string(other->name)) {
        return false;
    }
    if ((!this->value && other->value) || (this->value && !other->value)) {
        return false;
    }
    return strcmp(this->value, other->value) == 0;
}