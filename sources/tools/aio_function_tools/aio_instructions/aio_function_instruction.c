#include "../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"

aio_function_instruction *new_aio_function_instruction(aio_function_instruction_holder *holder,
                                                       aio_function_task_type task_type) {
    aio_function_instruction *instruction = new_object(sizeof(aio_function_instruction));
    instruction->holder = holder;
    instruction->task_type = task_type;
    return instruction;
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