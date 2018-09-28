#ifndef AIO_ASSIGN_TASK_H
#define AIO_ASSIGN_TASK_H

/**
 * 연결.
 */

#include <aio_runtime/aio_task/aio_task.h>

namespace lib4aio {

    class str_hook;
}

using namespace lib4aio;

template<typename T>
class aio_assign_task : public aio_task<T> {

public:

    explicit aio_assign_task();

    ~aio_assign_task();

    void perform(aio_ray<T> *ray);

    void set_name(str_hook *name);

    void set_value(char *value);

    const str_hook *get_name();

    const char *get_value();

private:

    str_hook *name;

    char *value;
};

#endif //AIO_ASSIGN_TASK_H