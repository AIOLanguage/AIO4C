#include "../../../lib/utils/string_utils/string_utils.h"
#include "../value/aio_value.h"
#include "../../../lib/utils/boolean_utils/boolean_utils.h"
#include "aio_variable_definition.h"

#ifndef AIO_VARIABLE_H
#define AIO_VARIABLE_H

typedef struct aio_variable {
    aio_variable_definition *variable_definition;
    aio_value *value;
} aio_variable;

aio_variable *new_aio_variable(const_string name, aio_value *value, const_boolean is_mutable_by_type, const_string type,
                               const_boolean is_mutable_by_value);

aio_variable *new_aio_variable_by_definition(aio_variable_definition *variable_definition, aio_value *value);

void delete_aio_variable(aio_variable *variable);

#endif //AIO_VARIABLE_H