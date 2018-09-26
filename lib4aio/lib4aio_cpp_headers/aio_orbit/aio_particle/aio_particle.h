#ifndef LIB4AIO_CPP_AIO_PARTICLE_H
#define LIB4AIO_CPP_AIO_PARTICLE_H

namespace lib4aio {

    class str_hook;

    template<class T>
    class aio_orbit;

    typedef enum aio_particle_signal {
        AIO_PARTICLE_SIGNAL_UNDEFINED, AIO_PARTICLE_SIGNAL_DETECTED, AIO_PARTICLE_SIGNAL_IS_READY
    } aio_particle_signal;

    template<class T>
    class aio_particle {

    public:

        aio_particle();

        void set_scanning_string_holder(const str_hook *string_holder);

        virtual ~aio_particle();

        virtual const aio_particle_signal handle_symbol(const unsigned position) = 0;

        virtual unsigned illuminate(T *container) = 0;

        virtual void reset();

    protected:

        const char *string;

        unsigned left_border;

        unsigned right_border;

        str_hook *token_holder;

        aio_particle_signal signal;

        bool is_inside_string;
    };
}

#endif //LIB4AIO_CPP_AIO_PARTICLE_H