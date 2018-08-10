#include <malloc.h>
#include "../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"

aio_instruction_holder *new_aio_instruction_holder(aio_instruction_holder *parent_holder) {
    aio_instruction_holder *holder = calloc(1, sizeof(aio_instruction_holder));
    holder->parent = parent_holder;
    holder->local_variable_definition_map = new_aio_variable_definition_map();
    holder->instruction_list = new_aio_instruction_list();
    return holder;
}

aio_instruction *new_aio_assign_instruction(aio_instruction_holder *holder, const_string source,
                                            const_string destination) {
    aio_instruction *instruction = calloc(1, sizeof(aio_instruction));
    instruction->holder = holder;
    instruction->task_type = AIO_ASSIGN_TASK;
    //Init task:
    aio_assign_task *task = calloc(1, sizeof(aio_assign_task));
    task->source = source;
    task->destination = destination;
    instruction->get.assign_task = task;
    return instruction;
}

aio_instruction *new_aio_break_instruction(aio_instruction_holder *holder) {
    aio_instruction *instruction = calloc(1, sizeof(aio_instruction));
    instruction->holder = holder;
    instruction->task_type = AIO_BREAK_TASK;
    return instruction;
}

aio_instruction *new_aio_if_instruction(aio_instruction_holder *holder, const_string if_condition,
                                        aio_instruction_holder *true_holder, aio_instruction_holder *false_holder) {
    aio_instruction *instruction = calloc(1, sizeof(aio_instruction));
    instruction->holder = holder;
    instruction->task_type = AIO_IF_TASK;
    //Init task:
    aio_if_task *task = calloc(1, sizeof(aio_if_task));
    task->if_condition = if_condition;
    task->true_holder = true_holder;
    task->false_holder = false_holder;
    instruction->get.if_task = task;
    return instruction;
}