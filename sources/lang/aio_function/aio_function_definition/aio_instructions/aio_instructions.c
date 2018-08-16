#include <malloc.h>
#include "../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"

aio_instruction_holder *new_aio_local_instruction_holder(aio_instruction_holder *parent_holder) {
    aio_instruction_holder *holder = new_object(sizeof(aio_instruction_holder));
    holder->parent = parent_holder;
    holder->variable_definition_map = new_aio_variable_definition_map();
    holder->instruction_list = new_aio_instruction_list();
    return holder;
}

aio_instruction *new_aio_assign_instruction(aio_instruction_holder *holder, const_string source,
                                            const_string destination) {
    aio_instruction *instruction = new_object(sizeof(aio_instruction));
    instruction->holder = holder;
    instruction->task_type = AIO_ASSIGN_TASK;
    //Init task:
    aio_assign_task *task = new_object(sizeof(aio_assign_task));
    task->value = new_string(source);
    task->variable_name = new_string(destination);
    instruction->get.assign_task = task;
    return instruction;
}

aio_instruction *new_aio_break_instruction(aio_instruction_holder *holder) {
    aio_instruction *instruction = new_object(sizeof(aio_instruction));
    instruction->holder = holder;
    instruction->task_type = AIO_BREAK_TASK;
    return instruction;
}

aio_instruction *new_aio_if_instruction(aio_instruction_holder *holder, const_string if_condition,
                                        aio_instruction_holder *true_holder, aio_instruction_holder *false_holder) {
    aio_instruction *instruction = new_object(sizeof(aio_instruction));
    instruction->holder = holder;
    instruction->task_type = AIO_IF_TASK;
    //Init task:
    aio_if_task *task = new_object(sizeof(aio_if_task));
    task->if_condition = if_condition;
    task->true_holder = true_holder;
    task->false_holder = false_holder;
    instruction->get.if_task = task;
    return instruction;
}

aio_instruction *new_aio_loop_instruction(aio_instruction_holder *holder, string loop_condition,
                                          aio_instruction_holder *init_holder, aio_instruction_holder *cycle_holder) {
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

aio_instruction *new_aio_return_instruction(aio_instruction_holder *holder, const string_list *return_value_list) {
    aio_instruction *instruction = new_object(sizeof(aio_instruction));
    instruction->holder = holder;
    instruction->task_type = AIO_RETURN_TASK;
    //Init task:
    aio_return_task *task = new_object(sizeof(aio_return_task));
    task->return_values = new_string_list();
    for (int i = 0; i < return_value_list->size; ++i) {
        string new_return_value = new_string(return_value_list->strings[i]);
        add_string_in_list(task->return_values, new_return_value);
    }
    instruction->get.return_task = task;
    return instruction;
}