#include <aio_runtime/aio_program_runtime.h>

aio_program_runtime::aio_program_runtime(aio_build_runtime *build_runtime) : aio_runtime(AIO_RUNTIME_TYPE_PROGRAM)
{
    this->build_runtime = build_runtime;
}

aio_program_runtime::~aio_program_runtime()
{}

aio_build_runtime *aio_program_runtime::get_build_runtime()
{
    return this->build_runtime;
}