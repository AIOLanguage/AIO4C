#ifndef AIO_RETURN_TASK_H
#define AIO_RETURN_TASK_H

#include <aio_runtime/aio_task/aio_task.h>

class aio_return_task : public aio_task {

public:

    aio_return_task();

    ~aio_return_task();

    void perform(aio_ray *ray);

    char *get_value();

    void set_value(char *value);

    bool operator==(const aio_task *task) const;

private:

    char *value;
};

#endif //AIO_RETURN_TASK_H