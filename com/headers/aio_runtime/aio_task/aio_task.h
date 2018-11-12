#ifndef AIO_TASK_H
#define AIO_TASK_H

class aio_ray;

class aio_task {

public:

    explicit aio_task();

    virtual ~aio_task();

    virtual void perform(aio_ray *ray) = 0;

    virtual bool operator==(const aio_task &rhs) const = 0;

    static bool compare(const aio_task *o1, const aio_task *o2);
};

#endif //AIO_TASK_H