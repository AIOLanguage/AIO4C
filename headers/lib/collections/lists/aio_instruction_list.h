#ifndef AIO_INSTRUCTION_LIST_H
#define AIO_INSTRUCTION_LIST_H

#include "../../../lang/aio_method/method_definition/instructions/aio_instruction_holder.h"
#include "../../../lang/aio_method/method_definition/instructions/aio_instruction_entry.h"

typedef struct aio_instruction_list {
    int capacity;
    int size;
    aio_instruction_entry **instruction_entries;
} aio_instruction_list;

#endif //AIO_INSTRUCTION_LIST_H