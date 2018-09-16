#include <aio_lang/aio_invokable/aio_invokable.h>
#include <aio_parsing/aio_circuit/aio_invokable_circuit.h>

aio_invokable::aio_invokable(
        const unsigned arg_count,
        aio_invokable_circuit *root_circuit,
        array_list<aio_class> *annotations
) : aio_annotatable(annotations)
{
    this->arg_count = arg_count;
    this->root_circuit = root_circuit;
}

aio_invokable::~aio_invokable()
{
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