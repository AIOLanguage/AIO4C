#ifndef LIB4AIO_CPP_AIO_PARTICLE_H
#define LIB4AIO_CPP_AIO_PARTICLE_H

#include <lib4aio_cpp_headers/aio_abstract/aio_abstract.h>

namespace lib4aio {

    class str_hook;

    template<class S>
    class aio_orbit;

    typedef enum aio_particle_signal {
        AIO_PARTICLE_SIGNAL_UNDEFINED, AIO_PARTICLE_SIGNAL_DETECTED, AIO_PARTICLE_SIGNAL_IS_READY
    } aio_particle_signal;

    template<class S>
    class aio_particle {

    public:

        aio_particle();

        void set_scanning_string_holder(const str_hook *string_holder);

        virtual ~aio_particle();

        virtual const aio_particle_signal handle_symbol(const unsigned position) = AIO_ABSTRACT;

        virtual unsigned illuminate(S *space) = AIO_ABSTRACT;

        virtual void reset() = AIO_ABSTRACT;

    protected:

        const char *string;

        unsigned left_border;

        unsigned right_border;

        str_hook *token_holder;

        aio_particle_signal signal;

        enum {
            AIO_BEYOND_STRING, AIO_INSIDE_STRING
        } string_mode;

        const bool is_beyond_string() const;
    };
}

#endif //LIB4AIO_CPP_AIO_PARTICLE_H