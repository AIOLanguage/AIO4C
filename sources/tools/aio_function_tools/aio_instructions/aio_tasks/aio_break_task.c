#include <tools/aio_function_tools/aio_instructions/aio_function_instruction.h>

aio_function_instruction *new_aio_break_instruction(aio_function_instruction_holder *holder)
{
    return new_aio_function_instruction(holder, AIO_BREAK_TASK);
}

aio_function_instruction *new_aio_continue_instruction(aio_function_instruction_holder *holder)
{
    return new_aio_function_instruction(holder, AIO_CONTINUE_TASK);
}

void perform_aio_break_instruction(const_aio_function_control_graph *control_graph)
{
    *control_graph->system_state_ref = AIO_FUNCTION_SYSTEM_BREAK;
}

void perform_aio_continue_instruction(const_aio_function_control_graph *control_graph)
{
    *control_graph->system_state_ref = AIO_FUNCTION_SYSTEM_CONTINUE;
}