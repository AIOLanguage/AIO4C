#ifndef AIO_INSTRUCTION_ENTRY_H
#define AIO_INSTRUCTION_ENTRY_H

#include "aio_instruction_holder.h"
#include "aio_instructions.h"

enum aio_instruction_type {
    ASSIGN, IF, SWITCH, LOOP, PROCEDURE, BREAK, OUT
};

typedef union aio_instruction_entry {
    enum aio_instruction_type instruction_type;
    aio_assign_instruction *assign_instruction;
    aio_if_instruction *if_instruction;
    aio_switch_instruction *switch_instruction;
    aio_loop_instruction *loop_instruction;
    aio_procedure_instruction *procedure_instruction;
    aio_break_instruction *break_instruction;
    aio_out_instruction *out_instruction;
} aio_instruction_entry;

#endif //AIO_INSTRUCTION_ENTRY_H