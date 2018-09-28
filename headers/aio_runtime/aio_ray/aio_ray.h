#ifndef AIO_RAY_H
#define AIO_RAY_H

namespace lib4aio {

    template<typename T>
    class array_list;
}

class aio_variable;

using namespace lib4aio;

typedef enum aio_ray_state {
    AIO_RAY_MAKE,
    AIO_RAY_BREAK,
    AIO_RAY_CONTINUE,
    AIO_RAY_STOP
} aio_ray_state;

template<typename T>
class aio_ray {

public:

    aio_ray();

    ~aio_ray();

    aio_ray<T> *perform(const T *container);

    void complete();

    array_list<aio_variable> *get_variables() const;

    const aio_ray_state get_state() const;

    void set_ray_state(aio_ray_state ray_state);

private:

    array_list<aio_variable> *variable_list;

    aio_ray_state *state;
};

#endif //AIO_RAY_H