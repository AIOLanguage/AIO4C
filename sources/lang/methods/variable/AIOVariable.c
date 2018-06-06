#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lang/methods/variable/AIOVariable.h"

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

void checkType(const enum AIOType *inputType, enum AIOType matcherType, char *value, int (*matcherFunction)(char *)) {
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

void createAIOVariable(AIOVariable **variable, char *name, char *value, int *mutable, enum AIOType *type) {
    //Need to crush a program:
    checkType(type, AIO_INT, value, matchesInt);
    checkType(type, AIO_DOU, value, matchesDou);
    checkType(type, AIO_CHA, value, matchesCha);
    checkType(type, AIO_STR, value, matchesStr);
    //Create the same variable:
    *variable = (AIOVariable *) calloc(1, sizeof(AIOVariable));
    //Set name:
    (*variable)->name = name;
    //Set value:
    (*variable)->value = value;
    //Set mutable:
    (*variable)->mutable = mutable;
    //Set type:
    (*variable)->type = type;
}