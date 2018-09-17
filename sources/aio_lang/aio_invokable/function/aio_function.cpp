#include <aio_lang/aio_invokable/aio_function/aio_function.h>

aio_function::aio_function(
        const unsigned arg_count,
        aio_invokable_circuit *root_circuit,
        str_hook *name,
        array_list<str_hook> *output_types,
        array_list<aio_class> *annotations,
        array_list<aio_function> *parents,
        aio_inherited_type inherited_type
) : aio_invokable(arg_count, root_circuit, output_types, annotations), aio_inheritable(parents, inherited_type)
{
    this->name = name;
}

aio_function::~aio_function()
{
    delete this->name;
}

const str_hook *aio_function::get_name() const
{
    return this->name;
}