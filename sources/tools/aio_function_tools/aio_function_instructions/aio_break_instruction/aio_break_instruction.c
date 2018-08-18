#include "../../../../../headers/tools/aio_function_tools/aio_function_instructions/aio_function_instruction_holder.h"
#include "../../../../../headers/tools/aio_function_tools/aio_function_instructions/aio_function_instruction.h"

aio_function_instruction * new_aio_break_instruction(
        aio_function_instruction_holder *holder) {
    aio_instruction *instruction = new_object(sizeof(aio_instruction));
    instruction->holder = holder;
    instruction->task_type = AIO_BREAK_TASK;
    return instruction;
}