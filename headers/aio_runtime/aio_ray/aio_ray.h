#ifndef AIO_RAY_H
#define AIO_RAY_H

namespace lib4aio {

    template<typename T>
    class array_list;
}

class aio_scheme;

class aio_variable;

using namespace lib4aio;

class aio_ray {

public:

    aio_ray(const aio_scheme *scheme);

    void perform();

    void complete();

    const array_list<aio_variable> *get_variables() const;

    ~aio_ray();

private:

    typedef enum aio_ray_state {

    };

    const aio_scheme *scheme;

    array_list<aio_variable> *variable_list;

    aio_ray_state *state;
};

#endif //AIO_RAY_H