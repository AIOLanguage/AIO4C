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

struct aio_space;

struct aio_class;

using namespace lib4aio;

class aio_class_particle : public aio_particle<aio_space> {

public:

    explicit aio_class_particle();

    ~aio_class_particle();

    const aio_particle_signal handle_symbol(const unsigned position);

    unsigned illuminate(aio_space *space);

    void reset();

private:

    unsigned counter_trigger;

    aio_class *clazz;

    enum {
        AIO_MONITOR_MODIFIER,
        AIO_MONITOR_NAME,
        AIO_MONITOR_ARROW_OR_COLON_OR_OPENING_BRACE,
        AIO_MONITOR_PARENT,
        AIO_MONITOR_COMMA_OR_COLON_OR_OPENING_BRACE,
        AIO_MONITOR_ATTRIBUTE,
        AIO_MONITOR_COLON_OR_OPENING_BRACE,
        AIO_MONITOR_BODY
    } monitor_mode;

    /**
     * State functions.
     */

    void monitor_modifier(const char symbol, const unsigned position);

    void monitor_name(const char symbol, const unsigned position);

    void monitor_arrow_or_colon_or_opening_brace(const char symbol, const unsigned position);

    void monitor_parent(const char symbol, const unsigned position);

    void monitor_comma_or_colon_or_opening_brace(const char symbol, const unsigned position);

    void monitor_attribute(const char symbol, const unsigned position);

    void monitor_colon_or_opening_brace(const char symbol, const unsigned position);

    void monitor_body(const char symbol, const unsigned position);

    /**
     * Transition functions.
     */

    void go_to_name_state();

    void go_to_arrow_or_colon_or_opening_brace_state(const char symbol, const unsigned position);

    void go_to_parent_state();

    void go_to_comma_or_colon_or_opening_brace_state(const char symbol, const unsigned position);

    void go_to_attribute_state();

    void go_to_body_state(const char symbol, const unsigned position);

    void go_to_colon_or_opening_brace_state(const char symbol, const unsigned position);

    /**
     * Operation functions.
     */

    void set_body();
};

#endif //AIO_CLASS_PARTICLE_H
#pragma clang diagnostic pop