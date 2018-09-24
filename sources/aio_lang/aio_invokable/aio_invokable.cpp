#include <aio_runtime/aio_scheme/aio_scheme.h>
#include <aio_lang/aio_invokable/aio_invokable.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>

using namespace lib4aio;

aio_invokable::aio_invokable()
{}

aio_invokable::~aio_invokable()
{
    this->output_types->free_elements();
    delete this->output_types;
    delete this->scheme;
}

const unsigned aio_invokable::get_arg_count() const
{
    return this->arg_count;
}

const array_list<str_hook> *aio_invokable::get_output_types() const
{
    return this->output_types;
}