#ifndef AIO_CLASS_TASK_H
#define AIO_CLASS_TASK_H

#include <aio_runtime/aio_task/aio_task.h>

class aio_class;

class aio_class_task : aio_task {

public:

    explicit aio_class_task(aio_class *class_ptr);

    ~aio_class_task();

    void perform(aio_ray<T> *ray);

    aio_class *class_ptr;
};

#endif //AIO_CLASS_TASK_H
