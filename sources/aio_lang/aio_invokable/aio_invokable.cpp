#include <aio_lang/aio_invokable/aio_invokable.h>
#include <aio_runtime/aio_invokable_circuit/aio_invokable_circuit.h>

aio_invokable::aio_invokable(
        const unsigned arg_count,
        aio_invokable_circuit *root_circuit,
        array_list<str_hook> *output_types,
        array_list<aio_class> *annotations
) : aio_annotatable(annotations)
{
    this->arg_count = arg_count;
    this->output_types = output_types;
    this->root_circuit = root_circuit;
}

aio_invokable::~aio_invokable()
{
    this->output_types->free_elements();
    delete this->output_types;
    delete this->root_circuit;
}

const unsigned aio_invokable::get_arg_count() const
{
    return this->arg_count;
}

const aio_invokable_circuit *aio_invokable::get_root_circuit() const
{
    return this->root_circuit;
}

const array_list<str_hook> *aio_invokable::get_output_types() const
{
    return this->output_types;
}