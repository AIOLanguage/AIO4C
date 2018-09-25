#include <aio_runtime/aio_build_runtime.h>

aio_build_runtime::aio_build_runtime() : aio_runtime(AIO_RUNTIME_TYPE_BUILD)
{}

aio_build_runtime::~aio_build_runtime()
{}

aio_variable *aio_build_runtime::get_main_property() const
{
    return this->main;
}

array_list<aio_variable> *aio_build_runtime::get_processors() const
{
    return this->processors;
}