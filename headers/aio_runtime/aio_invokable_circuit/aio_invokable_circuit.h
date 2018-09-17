#ifndef AIO_INVOKABLE_CIRCUIT_H
#define AIO_INVOKABLE_CIRCUIT_H

namespace lib4aio {

    template <class T> class array_list;

}

using namespace lib4aio;

class aio_field;

class aio_invokable_instruction;

class aio_invokable_circuit {
    aio_invokable_circuit *parent;
    array_list<aio_field> *field_definition_list;
    array_list<aio_invokable_instruction> *function_instruction_list;
};

#endif //AIO_INVOKABLE_CIRCUIT_H