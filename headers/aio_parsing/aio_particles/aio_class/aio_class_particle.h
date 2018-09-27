#ifndef AIO_CLASS_PARTICLE_H
#define AIO_CLASS_PARTICLE_H

/**
 * 연결.
 */

//lib4aio:
#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

namespace lib4aio {

    template<typename T>
    class array_list;
}

class aio_class;

class aio_class_task;

class aio_runtime;

using namespace lib4aio;

template<typename T>
class aio_class_particle : public aio_particle<T> {

public:

    explicit aio_class_particle(aio_runtime *runtime);

    ~aio_class_particle();

    const aio_particle_signal handle_symbol(const unsigned position);

    unsigned illuminate(T *space);

private:

    unsigned inner_iterator;

    aio_class *clazz;

    aio_runtime *runtime_ptr;

    array_list<aio_class> *class_list_ptr;

    enum {
        AIO_MONITOR_MODIFIER,
        AIO_MONITOR_NAME,
        AIO_MONITOR_KEY,
        AIO_MONITOR_PARENTS,
        AIO_MONITOR_ATTRIBUTES,
        AIO_MONITOR_BODY
    } monitor_mode;

    enum {
        AIO_TRIGGER_MODE_PASSIVE, AIO_TRIGGER_MODE_ACTIVE, AIO_TRIGGER_MODE_UNDEFINED
    } trigger_mode;

    aio_class_task *class_task;

    void monitor_class_modifier(const char symbol, const unsigned position);

    void monitor_class_name(const char symbol, const unsigned position);

    void monitor_class_key(const char symbol, const unsigned position);

    void monitor_class_parents(const char symbol, const unsigned position);

    void monitor_class_attributes(const char symbol, const unsigned position);

    void monitor_class_body(const char symbol, const unsigned position);

    void switch_particle_mode(const char symbol, const unsigned position);
};

#endif //AIO_CLASS_PARTICLE_H