#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lang/methods/variable/aio_variable.h"

//Passed JUnitTest!
char *removeBracketsAndReturnValue(char *value) {
    unsigned length = strlen(value);
    printf("VALUES\n");
    printf("%s\n", value);
    printf("%c\n", value[0]);
    printf("%c\n", value[length - 1]);
    if (value[0] == '\'' && value[length - 1] == '\'') {
        char *newValue = malloc(length - 2);
        for (int i = 1; i < length - 1; ++i) {
            newValue[i] = value[i];
        }
        free(&length);
        free(value);
        return newValue;
    } else {
        printf("\nThis is not char or str!");
        exit(1);
    }
}

//Passed JUnitTest!
void checkType(const enum aio_type *inputType, enum aio_type matcherType, char *value, int (*matcherFunction)(char *)) {
    if (*inputType == matcherType) {
        int matchesType = matcherFunction(value);
        if (matchesType == -1) {
            printf("Not matches %d!", matcherType);
            free(&matchesType);
            exit(1);
        }
        free(&matchesType);
    }
}

//Passed JUnitTest!
void new_aio_variable(aio_variable **variable, char *name, char *value, int mutable, enum aio_type *type) {
    //Need to crush a program:
    checkType(type, AIO_INT, value, matchesInt);
    checkType(type, AIO_DOU, value, matchesDou);
    checkType(type, AIO_CHA, value, matchesCha);
    checkType(type, AIO_STR, value, matchesStr);
    //Create the same variable:
    *variable = (aio_variable *) calloc(1, sizeof(aio_variable));
    //Set name:
    (*variable)->name = name;
    //Set value:
    (*variable)->value = value;
    //Set mutable:
    (*variable)->mutable = malloc(sizeof(int));
    *(*variable)->mutable = mutable;
    free(&mutable);
    //Set type:
    (*variable)->type = type;
}

/*
 * /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * int main(){
    aio_variable* aioVariable;
    enum aio_type aioType = AIO_STR;
    new_aio_variable(&aioVariable, "a", "'0.008'", 0, &aioType);
    printf("%s\n", aioVariable->name);
    printf("%s\n", aioVariable->value);
    printf("%d\n", *aioVariable->mutable);
    printf("%d\n", *aioVariable->type);
    return 0;
}
 */