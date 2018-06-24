#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lang/methods/result/aio_result.h"

void new_aio_int_result(aio_int_result **result, int acc, char *rest) {
    //Create the same result:
    *result = calloc(1, sizeof(aio_int_result));
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

void new_aio_dou_result(aio_dou_result **result, double acc, char *rest) {
    //Create the same result:
    *result = calloc(1, sizeof(aio_dou_result));
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

void new_aio_cha_result(aio_cha_result **result, char acc, char *rest) {
    //Create the same result:
    *result = malloc(sizeof(aio_cha_result));
    //Set acc:
    (*result)->acc = malloc(sizeof(char));
    *(*result)->acc = acc;
    free(&acc);
    //Set rest:
    (*result)->rest = rest;
}

void new_aio_str_result(aio_str_result **result, char *acc, char *rest) {
    //Create the same result:
    *result = malloc(sizeof(aio_cha_result));
    //Set acc:
    (*result)->acc = acc;
    //Set rest:
    (*result)->rest = rest;
}