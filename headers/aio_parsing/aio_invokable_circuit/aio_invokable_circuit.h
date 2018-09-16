#ifndef AIO_INVOKABLE_CIRCUIT_H
#define AIO_INVOKABLE_CIRCUIT_H

#include <aio_lang/aio_field/aio_field.h>
#include <aio_parsing/aio_invokable_instruction/aio_invokable_instruction.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>

class aio_invokable_circuit {
    aio_invokable_circuit *parent;
    array_list<aio_field> *field_definition_list;
    array_list<aio_invokable_instruction> *function_instruction_list;
};

#endif //AIO_INVOKABLE_CIRCUIT_H