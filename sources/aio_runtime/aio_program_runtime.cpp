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

void aio_program_runtime::set_entry_path(const char *entry_path)
{
    this->entry_path = entry_path;
}

const char *aio_program_runtime::get_entry_path() const
{
    return this->entry_path;
}
