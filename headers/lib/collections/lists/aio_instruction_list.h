#ifndef AIO_INSTRUCTION_LIST_H
#define AIO_INSTRUCTION_LIST_H

#include "../../../lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"

typedef struct aio_instruction_list {
    int capacity;
    int size;
    struct aio_instruction **instructions;
} aio_instruction_list;

aio_instruction_list *new_aio_instruction_list();

void add_aio_instruction_in_list(aio_instruction_list *list, struct aio_instruction *instruction);

void free_aio_instruction_list(aio_instruction_list *list);

#endif //AIO_INSTRUCTION_LIST_H