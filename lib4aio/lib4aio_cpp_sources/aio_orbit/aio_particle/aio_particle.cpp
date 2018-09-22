#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

namespace lib4aio {

    template<class S>
    aio_particle<S>::aio_particle()
    {
        this->is_inside_string = false;
    }

    template<class S>
    aio_particle<S>::~aio_particle()
    {}

    template<class S>
    void aio_particle<S>::set_scanning_string_holder(const str_hook *string_holder)
    {
        this->string = string_holder->get_string();
        this->left_border = string_holder->start;
        this->right_border = string_holder->end;
    }

    template<class S>
    const aio_particle_signal aio_particle<S>::handle_symbol(const unsigned position)
    {
        return AIO_PARTICLE_SIGNAL_DETECTED;
    }

    template<class S>
    unsigned aio_particle<S>::illuminate(S *space)
    {
        return 0;
    }

    template<class S>
    void aio_particle<S>::reset()
    {}
}