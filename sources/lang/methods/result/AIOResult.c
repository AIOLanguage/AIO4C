#include <malloc.h>
#include "../../../../headers/lang/methods/result/AIOResult.h"

void createAIOIntResult(AIOIntResult **result, int acc, char *rest) {
    //Create the same result:
    *result = malloc(sizeof(AIOIntResult));
    //Set acc:
    (*result)->acc = malloc(sizeof(int));
    *(*result)->acc = acc;
    free(&acc);
    //Set rest:
    (*result)->rest = rest;
}

void createAIODouResult(AIODouResult **result, double acc, char *rest) {
    //Create the same result:
    *result = malloc(sizeof(AIODouResult));
    //Set acc:
    (*result)->acc = malloc(sizeof(double));
    *(*result)->acc = acc;
    free(&acc);
    //Set rest:
    (*result)->rest = rest;
}

void createAIOChaResult(AIOChaResult **result, char acc, char *rest) {
    //Create the same result:
    *result = malloc(sizeof(AIOChaResult));
    //Set acc:
    (*result)->acc = malloc(sizeof(char));
    *(*result)->acc = acc;
    free(&acc);
    //Set rest:
    (*result)->rest = rest;
}

void createAIOStrResult(AIOStrResult **result, char *acc, char *rest) {
    //Create the same result:
    *result = malloc(sizeof(AIOChaResult));
    //Set acc:
    (*result)->acc = acc;
    //Set rest:
    (*result)->rest = rest;
}