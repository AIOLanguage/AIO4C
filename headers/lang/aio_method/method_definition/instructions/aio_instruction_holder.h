#ifndef AIO_INSTRUCTION_HOLDER_H
#define AIO_INSTRUCTION_HOLDER_H

#include "../../../../lib/collections/lists/string_list.h"
#include "../../../../lib/collections/maps/aio_variable_definition_map.h"
#include "../../../../lib/collections/lists/aio_instruction_list.h"
#include "aio_instruction_entry.h"

typedef struct aio_instruction_holder {
    aio_instruction_entry *parent_entry_instruction;
    //Keep string expression, key is index:
    aio_variable_definition_map *local_variable_definition_map;
    aio_instruction_list *instructions;
} aio_instruction_holder;

#endif //AIO_INSTRUCTION_HOLDER_H