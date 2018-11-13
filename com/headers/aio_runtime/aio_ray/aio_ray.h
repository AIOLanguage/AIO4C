#ifndef AIO_RAY_H
#define AIO_RAY_H

namespace lib4aio {

    template<typename T>
    class array_list;

    class str_hook;
}

struct aio_variable;

struct aio_schemable;

using namespace lib4aio;

typedef enum aio_ray_state {
    AIO_RAY_MAKE,
    AIO_RAY_BREAK,
    AIO_RAY_CONTINUE,
    AIO_RAY_STOP
} aio_ray_state;

class aio_ray {

public:

    aio_ray();

    ~aio_ray();

    aio_ray *perform(const aio_schemable *schemable);

    void complete();

    array_list<aio_variable> *get_variables() const;

    const aio_ray_state get_state() const;

    void set_ray_state(aio_ray_state ray_state);

    //TODO: Make non static while will be aio core:
    static bool is_available_name(const str_hook *name);

private:

    array_list<aio_variable> *variable_list;

    aio_ray_state *state;
};

#endif //AIO_RAY_H