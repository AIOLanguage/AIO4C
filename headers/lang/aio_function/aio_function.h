#include "../../lib/collections/maps/aio_variable_map.h"
#include "variable/aio_variable.h"
#include "../aio_context/aio_context.h"

#ifndef AIO_METHOD_H

typedef struct aio_function {
    aio_variable_map *variable_map;
} aio_function;

void invoke_new_aio_function(aio_context *aio_context, aio_function_definition *function_definition, aio_bundle *bundle);

boolean contains_variable(const_string variable_name, aio_function *function);

boolean contains_variable_in_map(const_string variable_name, aio_variable_map *variable_map);

void set_variable(aio_variable *variable, aio_function *function);

void close_aio_method(aio_function *method);

#endif //AIO_METHOD_H