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

    static aio_ray *create(const aio_scheme *scheme);

    aio_ray *perform();

    void complete();

    array_list<aio_variable> *get_variables() const;

private:

    typedef enum aio_ray_state {

    };

    const aio_scheme *scheme;

    array_list<aio_variable> *variable_list;

    aio_ray_state *state;

    aio_ray(const aio_scheme *scheme);

    ~aio_ray();
};

#endif //AIO_RAY_H