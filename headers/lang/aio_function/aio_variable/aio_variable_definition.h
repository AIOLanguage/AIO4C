#ifndef AIO_VARIABLE_DEFINITION_H
#define AIO_VARIABLE_DEFINITION_H

#include "../../../lib/utils/string_utils/string_utils.h"
#include "../../aio_types/aio_type.h"

typedef struct aio_variable_definition {
    string name;
    string type;
    boolean is_mutable_by_value;
} aio_variable_definition;

aio_variable_definition *new_aio_variable_definition(string name, string type,
                                                     const_boolean is_mutable_by_value);

void free_aio_variable_definition(aio_variable_definition *definition);

#endif //AIO_VARIABLE_DEFINITION_H