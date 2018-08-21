#ifndef AIO_VARIABLE_H
#define AIO_VARIABLE_H

#include "../../../lib/utils/string_utils/string_utils.h"
#include "../../../lib/utils/boolean_utils/boolean_utils.h"
#include "../aio_value/aio_value.h"
#include "aio_definition/aio_variable_definition.h"
#include "../../../tools/aio_function_tools/aio_instructions/aio_function_instruction_holder.h"

/**
 * Clumsy crutch...
 */

typedef struct aio_variable_definition;

/**
 * Variable.
 */

typedef struct aio_variable {
    const struct aio_variable_definition *variable_definition;
    struct aio_value *value;
} aio_variable;

struct aio_variable *new_aio_variable_by_definition(
        const struct aio_variable_definition *variable_definition,
        struct aio_value *value
);

struct aio_variable *get_variable_in_function_control_graph(
        const struct str_hook *variable_name,
        const struct aio_function_control_graph *control_graph
);

void free_aio_variable(struct aio_variable *variable);

/**
 * List.
 */

typedef struct aio_variable_list {
    unsigned int capacity;
    unsigned int size;
    struct aio_variable **variables;
} aio_variable_list;

struct aio_variable_list *new_aio_variable_list();

void add_aio_variable_in_list(struct aio_variable_list *list, struct aio_variable *variable);

struct aio_variable *get_aio_variable_in_list_by_name(
        const struct aio_variable_list *list,
        const struct str_hook *name
);

void free_aio_variable_list(struct aio_variable_list *list);

/**
 * Typedef utils.
 */

typedef const aio_variable const_aio_variable;

typedef aio_variable **aio_variable_array;

typedef const aio_variable **const_aio_variable_array;

typedef const aio_variable_list const_aio_variable_list;

#endif //AIO_VARIABLE_H