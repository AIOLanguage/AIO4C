#ifndef AIO_RETURN_TASK_H
#define AIO_RETURN_TASK_H

#include <aio_runtime/aio_task/aio_task.h>

class aio_return_task : public aio_task {

public:

    aio_return_task();

    ~aio_return_task();

    void perform(aio_ray *ray);

    bool equals(const aio_task *task) const;

    char *get_value();

    void set_value(char *value);

private:

    char *value;
};

#endif //AIO_RETURN_TASK_H