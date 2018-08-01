#ifndef AIO_AIO_VARIABLE_DEFINITION_H
#define AIO_AIO_VARIABLE_DEFINITION_H

#include "../../../lib/utils/string_utils/string_utils.h"
#include "../../aio_types/aio_type.h"

typedef struct aio_variable_definition {
    const_string name;
    enum aio_type *type;
    const_boolean is_mutable_by_value;
} aio_variable_definition;

aio_variable_definition *new_aio_variable_definition(const_string name, enum aio_type *type,
                                                     const_boolean is_mutable_by_value);

#endif //AIO_AIO_VARIABLE_DEFINITION_H