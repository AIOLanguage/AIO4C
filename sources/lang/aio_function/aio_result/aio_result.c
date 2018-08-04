#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lang/aio_function/aio_result/aio_result.h"

aio_result *new_aio_int_result(int int_acc, string rest) {
    //Create aio_result:
    aio_result *result = calloc(1, sizeof(aio_result));
    //Set int_acc:
    result->value->int_acc = int_acc;
    //Set rest:
    result->rest = rest;
    return result;
}

aio_result *new_aio_dou_result(double double_acc, string rest) {
    //Create the same aio_result:
    aio_result *result = calloc(1, sizeof(aio_result));
    //Set double_acc:
    result->value->double_acc = double_acc;
    //Set rest:
    result->rest = rest;
    return result;
}

aio_result *new_aio_str_result(string string_acc, string rest) {
    //Create the same aio_result:
    aio_result *result = calloc(1, sizeof(aio_result));
    //Set string_acc:
    result->value->string_acc = string_acc;
    //Set rest:
    result->rest = rest;
    return result;
}

aio_result *new_aio_boo_result(boolean boolean_acc, string rest) {
    //Create the same aio_result:
    aio_result *result = calloc(1, sizeof(aio_result));
    //Set boolean_acc:
    result->value->boolean_acc = boolean_acc;
    //Set rest:
    result->rest = rest;
    return result;
}