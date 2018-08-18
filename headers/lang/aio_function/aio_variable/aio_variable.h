#ifndef AIO_VARIABLE_H
#define AIO_VARIABLE_H

#include "../../../lib/utils/string_utils/string_utils.h"
#include "../../../lib/utils/boolean_utils/boolean_utils.h"
#include "aio_variable_definition.h"
#include "../aio_value/aio_value.h"
#include "../../../lib/utils/string_hook/str_hook.h"

typedef struct aio_variable {
    const_aio_variable_definition *variable_definition;
    aio_value *value;
} aio_variable;

typedef const aio_variable const_aio_variable;

aio_variable *new_aio_variable_by_definition(const_aio_variable_definition *variable_definition, aio_value *value);

void free_aio_variable(aio_variable *variable);

/**
 * List
 */

typedef struct aio_variable_list {
    size_t capacity;
    size_t size;
    aio_variable **variables;
} aio_variable_list;

typedef const aio_variable_list const_aio_variable_list;

aio_variable_list *new_aio_variable_list();

void add_aio_variable_in_list(aio_variable_list *list, aio_variable *variable);

aio_variable *get_aio_variable_in_list_by_name(const_aio_variable_list *list, const_str_hook *name);

void free_aio_variable_list(aio_variable_list *list);

#endif //AIO_VARIABLE_H