#ifndef AIO_INSTRUCTION_H
#define AIO_INSTRUCTION_H

template<typename T>
class aio_ray;

template <typename T> class aio_task {

public:

    explicit aio_task();

    virtual ~aio_task();

    virtual void perform(aio_ray<T> *ray) = 0;
};

#endif //AIO_INSTRUCTION_H