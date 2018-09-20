#ifndef LIB4AIO_CPP_AIO_PARTICLE_H
#define LIB4AIO_CPP_AIO_PARTICLE_H

namespace lib4aio {

    template<class S>
    class aio_orbit;

    typedef enum aio_particle_signal {
        AIO_PARTICLE_SIGNAL_UNDEFINED, AIO_PARTICLE_SIGNAL_DETECTED, AIO_PARTICLE_SIGNAL_IS_READY
    } aio_particle_signal;

    template<class S>
    class aio_particle {

    public:

        aio_particle();

        virtual ~aio_particle();

        void rotate_around(aio_orbit<S> *orbit);

        virtual const aio_particle_signal handle_symbol(const char symbol);

        virtual void illuminate(S *space);

        virtual void reset();

    private:

        aio_orbit<S> *parent_orbit;

    };
}

#endif //LIB4AIO_CPP_AIO_PARTICLE_H