#include "../../../../../headers/tools/aio_function_tools/aio_function_instructions/aio_function_instruction.h"

aio_function_instruction * new_aio_loop_instruction(
        struct aio_function_instruction_holder *holder, string loop_condition,
        struct aio_function_instruction_holder *init_holder, struct aio_function_instruction_holder *cycle_holder) {
    aio_instruction *instruction = new_object(sizeof(aio_instruction));
    instruction->holder = holder;
    instruction->task_type = AIO_LOOP_TASK;
    //Init task:
    aio_loop_task *task = new_object(sizeof(aio_loop_task));
    task->loop_condition = loop_condition;
    task->init_holder = init_holder;
    task->cycle_holder = cycle_holder;
    instruction->get.loop_task = task;
    return instruction;
}