#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lang/methods/result/aio_result.h"

aio_int_result *new_aio_int_result(int acc, char *rest) {
    //Create result:
    aio_int_result *result = calloc(1, sizeof(aio_int_result));
    if (result == NULL) {
        perror("cannot allocate memory for aio_int_result!");
        exit(1);
    }
    //Set acc:
    result->acc = acc;
    //Set rest:
    result->rest = rest;
    return result;
}

aio_dou_result *new_aio_dou_result(double acc, char *rest) {
    //Create the same result:
    aio_dou_result *result = calloc(1, sizeof(aio_dou_result));
    if (result == NULL) {
        perror("cannot allocate memory for aio_dou_result!");
        exit(1);
    }
    //Set acc:
    result->acc = acc;
    //Set rest:
    result->rest = rest;
    return result;
}

aio_cha_result *new_aio_cha_result(char acc, char *rest) {
    //Create the same result:
    aio_cha_result *result = calloc(1, sizeof(aio_cha_result));
    if (result == NULL) {
        perror("cannot allocate memory for aio_cha_result!");
        exit(1);
    }
    //Set acc:
    result->acc = acc;
    //Set rest:
    result->rest = rest;
    return result;
}

aio_str_result *new_aio_str_result(char *acc, char *rest) {
    //Create the same result:
    aio_str_result *result = calloc(1, sizeof(aio_str_result));
    if (result == NULL) {
        perror("cannot allocate memory for aio_str_result!");
        exit(1);
    }
    //Set acc:
    result->acc = acc;
    //Set rest:
    result->rest = rest;
    return result;
}