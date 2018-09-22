#ifndef AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_H
#define AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_H

#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

namespace lib4aio {

    class point_watcher;
}

using namespace lib4aio;

class aio_build_script_space;

class aio_build_script_attribute_particle : public aio_particle<aio_build_script_space> {

public:

    aio_build_script_attribute_particle();

    ~aio_build_script_attribute_particle();

    virtual const aio_particle_signal handle_symbol(const unsigned position);

    unsigned illuminate(aio_build_script_space *space);

    void reset();

private:

    unsigned whitespace_counter;

    enum {
        AIO_MONITOR_ATTRIBUTE, AIO_MONITOR_EQUAL_SIGN, AIO_MONITOR_VALUE
    } monitor_mode;

    enum {
        AIO_TRIGGER_MODE_PASSIVE, AIO_TRIGGER_MODE_ACTIVE
    } trigger_mode;

    struct {
        char *attribute;
        char *value;
    } config_materials;

    void handle_attribute_data(const char symbol, const unsigned position);

    void handle_equal_sign_data(const char symbol, const unsigned position);

    void handle_value_data(const char symbol, const unsigned position);
};

#endif //AIO_BUILD_SCRIPT_ATTRIBUTE_PARTICLE_H