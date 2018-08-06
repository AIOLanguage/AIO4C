#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lang/aio_types/aio_type.h"
#include "../../../../headers/lib/utils/double_utils/double_utils.h"
#include "../../../../headers/lib/utils/int_utils/int_utils.h"
#include "../../../../headers/lang/aio_function/aio_variable/aio_variable.h"

//Passed JUnitTest!
char *remove_brackets_and_return_value(string value) {
    unsigned length = strlen(value);
    if (value[0] == '\'' && value[length - 1] == '\'') {
        char *newValue = remove_prefix_suffix(value, "\'", "\'");
        free(value);
        return newValue;
    } else {
        printf("\nThis is not char or string_value!");
        exit(1);
    }
}

//Passed JUnitTest!
aio_variable *new_aio_variable(const_string name, union aio_value *value, const_string type,
                               const_boolean is_mutable_by_value) {
    aio_variable *variable = calloc(1, sizeof(aio_variable));
    variable->variable_definition = new_aio_variable_definition(name, type, is_mutable_by_value);
    //Set aio_value:
    variable->value = value;
    return variable;
}

aio_variable *new_aio_variable_by_definition(aio_variable_definition *variable_definition, union aio_value *value) {
    aio_variable *variable = calloc(1, sizeof(aio_variable));
    variable->variable_definition = variable_definition;
    variable->value = value;
    return variable;
}