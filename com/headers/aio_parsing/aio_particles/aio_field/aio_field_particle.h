#ifndef AIO_FIELD_PARTICLE_H
#define AIO_FIELD_PARTICLE_H

//lib4aio:
#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

namespace lib4aio {

    template<typename T>
    class array_list;

    class point_watcher;
}

struct aio_field;

struct aio_schemable;

class aio_assign_task;

using namespace lib4aio;

class aio_field_particle : public aio_particle<aio_schemable> {

public:

    explicit aio_field_particle();

    ~aio_field_particle();

    const aio_particle_signal handle_symbol(const unsigned position);

    unsigned illuminate(aio_schemable *container);

    void recycle();

private:

    unsigned whitespace_counter;

    aio_field *field;

    enum {
        AIO_MONITOR_MODIFIER,
        AIO_MONITOR_NAME,
        AIO_MONITOR_TYPE_OR_COLON_OR_EQUAL_SIGN,
        AIO_MONITOR_ATTRIBUTE,
        AIO_MONITOR_COLON_OR_EQUAL_SIGN_OR_SEMICOLON,
        AIO_MONITOR_VALUE
    } monitor_mode;

    aio_assign_task *task;

    /**
     * State functions.
     */

    void monitor_modifier(const char symbol, const unsigned position);

    void monitor_name(const char symbol, const unsigned position);

    void monitor_type_or_colon_or_equal_sign(const char symbol, const unsigned position);

    void monitor_attribute(const char symbol, const unsigned position);

    void monitor_value(const char symbol, const unsigned position);

    void monitor_colon_or_equal_sign_or_semicolon(const char symbol, const unsigned position);

    /**
     * Transition functions.
     */

    void go_to_name_state();

    void go_to_type_or_colon_or_equal_sign_state(const char symbol, const unsigned position);

    void go_to_value_state(const unsigned position);

    void go_to_attribute_state();

    void go_to_colon_or_equal_sign_or_semicolon_state(const char symbol, const unsigned position);

    /**
     * Option functions.
     */

    void set_value(const bool is_end_of_holder, const unsigned position);

    void set_null();

    void reset();
};

#endif //AIO_FIELD_PARTICLE_H