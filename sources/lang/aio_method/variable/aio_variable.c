#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lang/aio_method/variable/aio_variable.h"
#include "../../../../headers/lang/aio_types/aio_type.h"
#include "../../../../headers/lib/utils/double_utils/double_utils.h"
#include "../../../../headers/lib/utils/int_utils/int_utils.h"

//Passed JUnitTest!
char *remove_brackets_and_return_value(char *value) {
    unsigned length = strlen(value);
    if (value[0] == '\'' && value[length - 1] == '\'') {
        char *newValue = remove_prefix_suffix(value, "\'", "\'");
        free(value);
        return newValue;
    } else {
        printf("\nThis is not char or str!");
        exit(1);
    }
}

//Passed JUnitTest!
void check_type(const enum aio_type *input_type, enum aio_type matcher_type, char *value,
                int (*matcher_function)(char *)) {
    if (*input_type == matcher_type) {
        int matches_type = matcher_function(value);
        if (matches_type == -1) {
            perror("not matches type!");
            exit(1);
        }
    }
}

//Passed JUnitTest!

aio_variable *new_aio_variable(const_string name, aio_value *value, const_boolean is_mutable_by_type, const_string type,
                               const_boolean is_mutable_by_value) {
    //Create the same variable:
    aio_variable *variable = calloc(1, sizeof(aio_variable));
    variable->variable_definition = new_aio_variable_definition(name, );
    //Set value:
    variable->value = value;
    //Set is_mutable_by_type:
    variable->mutable_by_type = is_mutable_by_type;
    //Set type:
    variable->type = type;
    return variable;
}