#ifndef AIO_VARIABLE_DEFINITION_H
#define AIO_VARIABLE_DEFINITION_H

#include "../../../../lib/utils/string_utils/string_utils.h"
#include "../aio_variable.h"
#include "../../../../lib/utils/str_hook/str_hook.h"

typedef struct aio_function_instruction_holder;

typedef struct aio_variable_definition {
    const_str_hook *name;
    str_hook *type;
    boolean is_mutable_by_value;
} aio_variable_definition;

typedef const aio_variable_definition const_aio_variable_definition;

aio_variable_definition *new_aio_variable_definition(const_str_hook *name, str_hook *type,
                                                     const_boolean is_mutable_by_value);

const_aio_variable_definition *get_variable_definition_in_function_tree(const_str_hook *variable_name,
                                                                        const struct aio_function_instruction_holder
                                                                        *holder);

void free_aio_variable_definition(aio_variable_definition *definition);

/**
 * List.
 */

typedef struct aio_variable_definition_list {
    size_t capacity;
    size_t size;
    const aio_variable_definition **definitions;
} aio_variable_definition_list;

typedef const aio_variable_definition_list const_aio_variable_definition_list;

aio_variable_definition_list *new_aio_variable_definition_list();

void add_aio_variable_definition_in_list(aio_variable_definition_list *list, const_aio_variable_definition *definition);

const_aio_variable_definition *get_aio_variable_definition_in_map_by_name(const_aio_variable_definition_list *list,
                                                                          const_str_hook *name);

void free_aio_variable_definition_list(aio_variable_definition_list *list);

const struct aio_variable_list *upbuild_variable_map_by_definitions(const_aio_variable_definition_list *list);

#endif //AIO_VARIABLE_DEFINITION_H