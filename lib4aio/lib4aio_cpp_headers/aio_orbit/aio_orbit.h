#ifndef LIB4AIO_CPP_AIO_ORBIT_H
#define LIB4AIO_CPP_AIO_ORBIT_H

namespace lib4aio {

    class str_hook;

    template<class T>
    class array_list;

    template<class S>
    class aio_particle;

    template<class S>
    class aio_orbit {

        typedef enum particle_mode {
            AIO_ALL_PARTICLES_SCAN, AIO_ONE_PARTICLE_SCAN
        } aio_particle_mode;

    public:

        aio_orbit();

        virtual ~aio_orbit();

        S *launch(const str_hook *string_holder);

    protected:

        virtual S *new_space();

        virtual array_list<aio_particle<S>> *create_particle_list();

    private:

        aio_particle_mode mode;

        array_list<aio_particle<S>> *particle_list;

        aio_particle<S> *current_particle;

        void reset_particles();

        void illuminate(S space);

        unsigned position;
    };
}

#endif //LIB4AIO_CPP_AIO_ORBIT_H