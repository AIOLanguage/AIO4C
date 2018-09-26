#ifndef LIB4AIO_CPP_AIO_ORBIT_H
#define LIB4AIO_CPP_AIO_ORBIT_H

#include <functional>

namespace lib4aio {

    class str_hook;

    template<class T>
    class array_list;

    template<class T>
    class aio_particle;

    template<class T>
    class aio_orbit {

    public:

        explicit aio_orbit(array_list <aio_particle<T>> *particle_list, std::function<T *()> new_container_func);

        virtual ~aio_orbit();

        T *make(const str_hook *string_holder);

    private:

        std::function<T *()> new_space_func;

        array_list<aio_particle<T>> *particle_list;

        enum {
            AIO_ALL_PARTICLES_SCAN, AIO_ONE_PARTICLE_SCAN
        } particle_mode;

        aio_particle<T> *active_particle;

        unsigned iterator_position;

        void reset_particles();

        void illuminate(T *space);
    };
}

#endif //LIB4AIO_CPP_AIO_ORBIT_H