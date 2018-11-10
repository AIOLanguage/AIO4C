#ifndef AIO_FUNCTION_PARTICLE_H
#define AIO_FUNCTION_PARTICLE_H

#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

namespace lib4aio {

    template<typename T>
    class array_list;
}

using namespace lib4aio;

struct aio_space;

struct aio_function;

class aio_function_particle : public aio_particle<aio_space> {

public:

    aio_function_particle();

    ~aio_function_particle();

    const aio_particle_signal handle_symbol(const unsigned position);

    unsigned illuminate(aio_space *space);

    void reset();

private:

    enum {
        AIO_MONITOR_MODIFIER,
        AIO_MONITOR_NAME,
        AIO_MONITOR_ARGS,
        AIO_MONITOR_TYPE_OR_COLON_OR_EQUAL_SIGN_OR_OPENING_BRACE,
        AIO_MONITOR_ATTRIBUTE,
        AIO_MONITOR_BODY,
        AIO_MONITOR_VALUE,
        AIO_MONITOR_COLON_OR_EQUAL_SIGN_OR_OPENING_BRACE
    } monitor_mode;

    unsigned counter_trigger;

    aio_function *function;

    /**
     * State functions.
     */

    void monitor_modifier(const char symbol, const unsigned position);

    void monitor_name(const char symbol, const unsigned position);

    void monitor_args(const char symbol, const unsigned position);

    void monitor_type_or_colon_or_equal_sign_or_opening_brace(const char symbol, const unsigned position);

    void monitor_attribute(const char symbol, const unsigned position);

    void monitor_body(const char symbol, const unsigned position);

    void monitor_value(const char symbol, const unsigned position);

    void monitor_colon_or_equal_sign_or_opening_brace(const char symbol, const unsigned position);

    /**
     * Transition functions.
     */

    void go_to_name_state();

    void go_to_args_state(const char symbol, const unsigned position);

    void go_to_type_or_colon_or_equal_sign_or_opening_brace_state(const char symbol, const unsigned position);

    void go_to_attribute_state();

    void go_to_body_state(const char symbol, const unsigned position);

    void go_to_value_state(const unsigned position);

    void go_to_colon_or_equal_sign_or_opening_brace_state(const char symbol, const unsigned position);

    /**
     * Operation functions.
     */

    void set_args();

    void set_single_return_instruction(const bool is_end_of_holder, const unsigned position);

    void set_body();
};

#endif //AIO_FUNCTION_PARTICLE_H