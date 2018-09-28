#ifndef AIO_TASK_H
#define AIO_TASK_H

template<typename T>
class aio_ray;

template<typename T>
class aio_task {

public:

    explicit aio_task();

    virtual ~aio_task();

    virtual void perform(aio_ray<T> *ray) = 0;
};

#endif //AIO_TASK_H