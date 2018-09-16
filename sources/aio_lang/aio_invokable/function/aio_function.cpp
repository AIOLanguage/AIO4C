#include <aio_lang/aio_invokable/aio_function/aio_function.h>

aio_function::aio_function(
        const unsigned arg_count,
        aio_invokable_circuit *root_circuit,
        str_hook *name,
        array_list<str_hook> *output_types,
        array_list<aio_class> *annotations
) : aio_invokable(arg_count, root_circuit, annotations)
{
    this->name = name;
    this->output_types = output_types;
}

aio_function::~aio_function()
{
    this->output_types->free_elements();
    delete this->output_types;
    delete this->name;
}

const str_hook *aio_function::get_name() const
{
    return this->name;
}

const array_list<str_hook> *aio_function::get_output_types() const
{
    return this->output_types;
}
