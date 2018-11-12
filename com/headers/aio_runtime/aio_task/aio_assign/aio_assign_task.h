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

class aio_assign_task : public aio_task {

public:

    explicit aio_assign_task();

    ~aio_assign_task();

    void perform(aio_ray *ray);

    bool equals(const aio_task *task) const;

    void set_name(str_hook *name);

    void set_value(char *value);

    const str_hook *get_name() const;

    const char *get_value() const;

    bool operator==(const aio_task *task) const;

private:

    str_hook *name;

    char *value;
};

#endif //AIO_ASSIGN_TASK_H