#ifndef AIO_FUNCTION_PARTICLE_H
#define AIO_FUNCTION_PARTICLE_H

#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

namespace lib4aio {

    template<typename T>
    class array_list;
}

using namespace lib4aio;

class aio_runtime;

class aio_function;

template<typename T>
class aio_function_particle : public aio_particle<T> {

public:

    aio_function_particle(aio_runtime *runtime, array_list<aio_function> *function_list);

    ~aio_function_particle();

    const aio_particle_signal handle_symbol(const unsigned position);

    unsigned illuminate(T *space);

private:

    enum {
        AIO_MONITOR_MODIFIER,
        AIO_MONITOR_NAME,
        AIO_MONITOR_ARGS,
        AIO_MONITOR_OUTPUT_TYPE,
        AIO_MONITOR_BODY
    } monitor_mode;

    unsigned iterator;

    aio_function *function;

    void monitor_function_modifier(const char symbol, const unsigned position);

    void monitor_function_name(const char symbol, const unsigned position);

    void monitor_function_args(const char symbol, const unsigned position);

    void monitor_function_output_type(const char symbol, const unsigned position);

    void monitor_function_body(const char symbol, const unsigned position);
};

#endif //AIO_FUNCTION_PARTICLE_H