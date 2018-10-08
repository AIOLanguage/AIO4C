#ifndef AIO_TASK_H
#define AIO_TASK_H

class aio_ray;

class aio_task {

public:

    explicit aio_task();

    virtual ~aio_task();

    virtual void perform(aio_ray *ray) = 0;
};

#endif //AIO_TASK_H