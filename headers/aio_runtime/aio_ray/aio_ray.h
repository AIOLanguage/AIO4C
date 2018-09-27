#ifndef AIO_RAY_H
#define AIO_RAY_H

namespace lib4aio {

    template<typename T>
    class array_list;
}

class aio_variable;

using namespace lib4aio;


typedef enum aio_ray_state {
    AIO_RAY_NORMAL
};

template<typename T>
class aio_ray {

public:

    aio_ray();

    ~aio_ray();

    aio_ray *perform(const T *container);

    array_list<aio_variable> *get_variables() const;

private:

    array_list<aio_variable> *variable_list;

    aio_ray_state *state;
};

#endif //AIO_RAY_H