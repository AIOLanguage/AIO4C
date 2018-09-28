#ifndef AIO_FIELD_PARTICLE_H
#define AIO_FIELD_PARTICLE_H

//lib4aio:
#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

namespace lib4aio {

    template<typename T>
    class array_list;

    class point_watcher;
}

class aio_field;

template<typename T>
class aio_assign_task;

using namespace lib4aio;

template<typename T>
class aio_field_particle : public aio_particle<T> {

public:

    explicit aio_field_particle(array_list<str_hook> *type_list_ptr, array_list<aio_field> *field_list_ptr);

    ~aio_field_particle();

    const aio_particle_signal handle_symbol(const unsigned position);

    unsigned illuminate(T *container);

    void reset();

private:

    unsigned whitespace_counter;

    aio_field *field;

    array_list<str_hook> *type_list_ptr;

    array_list<aio_field> *field_list_ptr;

    enum {
        AIO_MONITOR_MODIFIER,
        AIO_MONITOR_NAME,
        AIO_MONITOR_TYPE,
        AIO_MONITOR_EQUAL_SIGN,
        AIO_MONITOR_VALUE
    } monitor_mode;

    aio_assign_task<T> *assign_task;

    void monitor_field_modifier(const char symbol, const unsigned position);

    void monitor_field_name(const char symbol, const unsigned position);

    void monitor_field_type(const char symbol, const unsigned position);

    void monitor_equal_sign(const char symbol, const unsigned position);

    void monitor_value(const char symbol, const unsigned position);
};

#endif //AIO_FIELD_PARTICLE_H