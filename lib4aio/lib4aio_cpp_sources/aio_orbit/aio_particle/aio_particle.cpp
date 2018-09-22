#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

namespace lib4aio {

    template<class S>
    aio_particle<S>::aio_particle()
    {
        this->string_mode = AIO_BEYOND_STRING;
    }

    template<class S>
    aio_particle<S>::~aio_particle()
    {}

    template<class S>
    const bool aio_particle<S>::is_beyond_string() const
    {
        return this->string_mode == AIO_BEYOND_STRING;
    }

    template<class S>
    void aio_particle<S>::set_scanning_string_holder(const str_hook *string_holder)
    {
        this->string = string_holder->get_string();
        this->left_border = string_holder->start;
        this->right_border = string_holder->end;
    }
}