#include "../../../lib/utils/string_utils/string_utils.h"
#include "../value/aio_value.h"
#include "../../../lib/utils/boolean_utils/boolean_utils.h"

#ifndef AIO_VARIABLE_H
#define AIO_VARIABLE_H

typedef struct aio_variable {
    const_string name;
    aio_value *value;
    boolean mutable_by_type;
    boolean mutable_by_value;
    enum aio_type *type;
} aio_variable;

aio_variable *new_aio_variable(const_string name, aio_value *value, boolean mutable, enum aio_type *type);

void delete_aio_variable(aio_variable *variable);

#endif //AIO_VARIABLE_H