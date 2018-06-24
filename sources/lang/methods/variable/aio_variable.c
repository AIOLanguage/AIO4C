#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lang/methods/variable/aio_variable.h"
#include "../../../../headers/lib/utils/string_utils/string_utils.h"

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
aio_variable *new_aio_variable(char *name, char *value, int mutable, enum aio_type *type) {
    //Need to crush a program:
    check_type(type, AIO_INT, value, matches_int);
    check_type(type, AIO_DOU, value, matches_dou);
    check_type(type, AIO_CHA, value, matches_cha);
    check_type(type, AIO_STR, value, matches_str);
    //Create the same variable:
    aio_variable *variable = calloc(1, sizeof(aio_variable));
    if (variable == NULL) {
        perror("cannot allocate memory for aio_variable!");
        exit(1);
    }
    //Set name:
    variable->name = name;
    //Set value:
    variable->value = value;
    //Set mutable:
    variable->mutable = mutable;
    //Set type:
    variable->type = type;
    return variable;
}