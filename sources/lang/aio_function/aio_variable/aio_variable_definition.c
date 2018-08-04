#include <malloc.h>
#include "../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../headers/lang/aio_function/aio_variable/aio_variable_definition.h"

aio_variable_definition *new_aio_variable_definition(const_string name, const_string type,
                                                     const_boolean is_mutable_by_value) {
    aio_variable_definition *definition = calloc(1, sizeof(aio_variable_definition));
    definition->name = name;
    definition->type = type;
    definition->is_mutable_by_value = is_mutable_by_value;
    return definition;
}

void delete_aio_variable_definition(aio_variable_definition *definition) {

}
