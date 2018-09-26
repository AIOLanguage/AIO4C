#ifndef AIO_FIELD_PARTICLE_H
#define AIO_FIELD_PARTICLE_H

#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

namespace lib4aio {

    class point_watcher;
}

using namespace lib4aio;

template<typename T>
class aio_field_particle : public aio_particle<T> {

public:

    explicit aio_field_particle();

    ~aio_field_particle();

    const aio_particle_signal handle_symbol(const unsigned position);

    unsigned illuminate(T *container);

    void reset();

private:

    unsigned whitespace_counter;

    enum {
        AIO_MONITOR_ATTRIBUTE, AIO_MONITOR_EQUAL_SIGN, AIO_MONITOR_VALUE
    } monitor_mode;

    enum {
        AIO_TRIGGER_MODE_PASSIVE, AIO_TRIGGER_MODE_ACTIVE, AIO_TRIGGER_MODE_UNDEFINED
    } trigger_mode;

    struct {
        char *attribute;
        char *value;
    } config_materials;

    void handle_field_data(const char symbol, const unsigned position);

    void handle_equal_sign_data(const char symbol, const unsigned position);

    void handle_value_data(const char symbol, const unsigned position);
};

#endif //AIO_FIELD_PARTICLE_H