#include <aio_runtime/aio_task/aio_task.h>

aio_task::aio_task()
{}

aio_task::~aio_task()
{}

bool aio_task::compare(const aio_task *o1, const aio_task *o2)
{
    return *o1 == o2;
}