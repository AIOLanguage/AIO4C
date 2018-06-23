#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lang/methods/result/AIOResult.h"

void createAIOIntResult(AIOIntResult **result, int acc, char *rest) {
    //Create the same result:
    *result = calloc(1, sizeof(AIOIntResult));
    if (*result == NULL){
        perror("cannot allocate memory for aioIntResult!");
        exit(1);
    }
    //Set acc:
    (*result)->acc = calloc(1, sizeof(int));
    if ((*result)->acc == NULL){
        perror("cannot allocate memory for acc in aioIntResult!");
        exit(1);
    }
    *(*result)->acc = acc;
    //Set rest:
    (*result)->rest = rest;
}

void createAIODouResult(AIODouResult **result, double acc, char *rest) {
    //Create the same result:
    *result = calloc(1, sizeof(AIODouResult));
    if (*result == NULL){
        perror("cannot allocate memory for aioDouResult!");
        exit(1);
    }
    //Set acc:
    (*result)->acc = calloc(1, sizeof(double));
    if ((*result)->acc == NULL){
        perror("cannot allocate memory for acc in aioDouResult!");
        exit(1);
    }
    *(*result)->acc = acc;
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