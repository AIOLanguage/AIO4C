#include <lib4aio_cpp_headers/aio_orbit/aio_orbit.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>
#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>
#include <lib4aio_cpp_sources/aio_orbit/aio_particle/aio_particle.cpp>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

namespace lib4aio {

    template<class S>
    aio_orbit<S>::aio_orbit(array_list <aio_particle<S>> *particle_list, function<S *()> new_container_func)
    {
        this->particle_list = particle_list;
        this->new_space_func = new_container_func;
        this->particle_mode = AIO_ALL_PARTICLES_SCAN;
    }

    template<class S>
    aio_orbit<S>::~aio_orbit()
    {
        this->particle_list->free_elements();
        delete this->particle_list;
    }

    template<class S>
    void aio_orbit<S>::reset_particles()
    {
        const unsigned list_size = particle_list->get_size();
        //Provide parent to children:
        for (unsigned i = 0; i < list_size; ++i) {
            aio_particle<S> *particle = particle_list->get(i);
            particle->reset();
        }
    }

    template<class S>
    void aio_orbit<S>::illuminate(S *space)
    {
        this->iterator_position = this->active_particle->illuminate(space);
        this->particle_mode = AIO_ALL_PARTICLES_SCAN;
        this->active_particle = nullptr;
        this->reset_particles();
    }

    template<class S>
    S *aio_orbit<S>::make(const str_hook *string_holder)
    {
        S *space = new_space_func();
        const unsigned list_size = this->particle_list->get_size();
        //문자열 소유자를 놓다:
        for (unsigned i = 0; i < list_size; ++i) {
            this->particle_list->get(i)->set_scanning_string_holder(string_holder);
        }
        //스캔 시작:
        this->iterator_position = string_holder->start;
        while (this->iterator_position < string_holder->end) {
            if (this->particle_mode == AIO_ALL_PARTICLES_SCAN) {
                for (unsigned i = 0; i < list_size; ++i) {
                    aio_particle<S> *particle = particle_list->get(i);
                    const aio_particle_signal signal = particle->handle_symbol(this->iterator_position);
                    if (signal == AIO_PARTICLE_SIGNAL_DETECTED) {
                        this->active_particle = particle;
                        this->particle_mode = AIO_ONE_PARTICLE_SCAN;
                        break;
                    }
                    if (signal == AIO_PARTICLE_SIGNAL_IS_READY) {
                        this->illuminate(space);
                    }
                }
            } else {
                aio_particle<S> *particle = this->active_particle;
                aio_particle_signal signal = particle->handle_symbol(this->iterator_position);
                if (signal == AIO_PARTICLE_SIGNAL_IS_READY) {
                    this->active_particle = particle;
                    this->illuminate(space);
                }
            }
            this->iterator_position++;
        }
        return space;
    }
}