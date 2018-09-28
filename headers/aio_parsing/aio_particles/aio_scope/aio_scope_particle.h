#ifndef AIO_SCOPE_PARTICLE_H
#define AIO_SCOPE_PARTICLE_H

#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

namespace lib4aio {

    template<typename T>
    class array_list;
}

using namespace lib4aio;

class aio_runtime;

class aio_scope;

template<typename T>
class aio_scope_particle : public aio_particle<T> {

public:

    aio_scope_particle(aio_runtime *runtime_ptr, array_list<aio_scope> *scope_list_ptr);

    ~aio_scope_particle();

    const aio_particle_signal handle_symbol(const unsigned position);

    unsigned illuminate(T *space);

private:

    aio_runtime *runtime_ptr;

    aio_scope *scope;

    array_list<aio_scope> *scope_list_ptr;

    enum {
        AIO_MONITOR_MODIFIER,
        AIO_MONITOR_NAME,
        AIO_MONITOR_KEY,
        AIO_MONITOR_ATTRIBUTES,
        AIO_MONITOR_BODY
    } monitor_mode;


    void monitor_scope_modifier(const char symbol, const unsigned position);

    void monitor_scope_name(const char symbol, const unsigned position);

    void monitor_scope_key(const char symbol, const unsigned position);

    void monitor_scope_attributes(const char symbol, const unsigned position);

    void monitor_scope_body(const char symbol, const unsigned position);

    void switch_monitor_mode(const char symbol, const unsigned position);
};

#endif //AIO_SCOPE_PARTICLE_H