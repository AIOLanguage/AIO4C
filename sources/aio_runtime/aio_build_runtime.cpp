#include <aio_runtime/aio_build_runtime.h>

aio_build_runtime::aio_build_runtime() : aio_runtime(AIO_RUNTIME_TYPE_BUILD)
{}

aio_build_runtime::~aio_build_runtime()
{}

aio_variable *aio_build_runtime::get_main_property_ptr() const
{
    return this->main_ptr;
}

array_list<aio_variable> *aio_build_runtime::get_processors_ptr() const
{
    return this->processors_ptr;
}