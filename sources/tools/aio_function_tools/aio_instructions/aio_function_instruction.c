#include "../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_assign_task.h"
#include "../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_break_task.h"
#include "../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_if_task.h"
#include "../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_loop_task.h"
#include "../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_procedure_task.h"
#include "../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_return_task.h"
#include "../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_switch_task.h"
#include "../../../../headers/tools/aio_function_tools/aio_control_graph/aio_function_control_graph.h"

aio_function_instruction *new_aio_function_instruction(aio_function_instruction_holder *holder,
                                                       aio_function_task_type task_type) {
    aio_function_instruction *instruction = new_object(sizeof(aio_function_instruction));
    instruction->holder = holder;
    instruction->task_type = task_type;
    return instruction;
}

void perform_aio_instruction(const_aio_function_instruction *instruction,
                             const_aio_function_control_graph *control_graph) {
    aio_function_task_type task_type = instruction->task_type;
    switch (task_type) {
        case AIO_ASSIGN_TASK:
            perform_aio_assign_instruction(instruction, control_graph);
            break;
        case AIO_BREAK_TASK:
            perform_aio_break_instruction(control_graph);
            break;
        case AIO_CONTINUE_TASK:
            perform_aio_continue_instruction(control_graph);
            break;
        case AIO_IF_TASK:
            perform_aio_if_instruction(instruction, control_graph);
            break;
        case AIO_LOOP_TASK:
            perform_aio_loop_instruction(instruction, control_graph);
            break;
        case AIO_PROCEDURE_TASK:
            perform_aio_procedure_instruction(instruction, control_graph);
            break;
        case AIO_RETURN_TASK:
            perform_aio_return_instruction(instruction, control_graph);
            break;
        case AIO_SWITCH_TASK:
            perform_aio_switch_instruction(instruction, control_graph);
    }
}

/**
 * Define only list.
 */

aio_function_instruction_list *new_aio_function_instruction_list() {
    aio_function_instruction_list *list = new_object(sizeof(aio_function_instruction_list));
    list->capacity = 2;
    list->size = 0;
    list->instructions = new_object_array(2, sizeof(aio_function_instruction *));
    return list;
}

void update_memory_in_instruction_list(aio_function_instruction_list *list) {
    if (list->size + 1 == list->capacity) {
        list->capacity = list->capacity * 2;
        list->instructions = realloc(list->instructions, list->capacity * sizeof(aio_function_instruction *));
    }
}

void add_aio_instruction_in_list(aio_function_instruction_list *list, const_aio_function_instruction *instruction) {
    update_memory_in_instruction_list(list);
    list->instructions[list->size] = instruction;
    list->size++;
}

void free_aio_instruction_list(aio_function_instruction_list *list) {
    free(list->instructions);
    free(list);
}