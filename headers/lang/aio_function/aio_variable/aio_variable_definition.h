#ifndef AIO_VARIABLE_DEFINITION_H
#define AIO_VARIABLE_DEFINITION_H

#include "../../../lib/utils/string_utils/string_utils.h"
#include "../../aio_types/aio_type.h"
#include "../../../tools/aio_function_tools/aio_function_instructions/aio_function_instruction_holder.h"

typedef struct aio_function_instruction_holder;

typedef struct aio_variable_definition {
    const_str_hook *name;
    string type;
    const_boolean is_mutable_by_value;
} aio_variable_definition;

typedef const aio_variable_definition const_aio_variable_definition;

aio_variable_definition *new_aio_variable_definition(string name, string type,
                                                     const_boolean is_mutable_by_value);

const_aio_variable_definition *get_variable_definition_in_function_tree(const_str_hook variable_name,
                                                                        const struct aio_function_instruction_holder
                                                                        *child_holder);

void free_aio_variable_definition(aio_variable_definition *definition);

/**
 * List.
 */

typedef struct aio_variable_definition_list {
    size_t capacity;
    size_t size;
    aio_variable_definition **variable_definitions;
} aio_variable_definition_list;

typedef const aio_variable_definition_list const_aio_variable_definition_list;

aio_variable_definition_list *new_aio_variable_definition_map();

void put_aio_variable_definition_in_map(aio_variable_definition_list *map, aio_variable_definition *definition);

aio_variable_definition *
get_aio_variable_definition_in_map_by_name(aio_variable_definition_list *map, const_string name);

void delete_aio_variable_definition_map(aio_variable_definition_list *map);

#endif //AIO_VARIABLE_DEFINITION_H