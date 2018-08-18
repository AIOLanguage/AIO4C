#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lang/aio_function/aio_result/aio_result.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"

aio_result *new_aio_int_result(const int int_acc, str_hook *rest) {
    aio_result *result = new_object(sizeof(aio_result));
    result->value->int_acc = int_acc;
    result->rest = rest;
    return result;
}

aio_result *new_aio_dou_result(const double double_acc, str_hook *rest) {
    aio_result *result = new_object(sizeof(aio_result));
    result->value->double_acc = double_acc;
    result->rest = rest;
    return result;
}

aio_result *new_aio_str_result(string string_acc, str_hook *rest) {
    aio_result *result = new_object(sizeof(aio_result));
    result->value->string_acc = string_acc;
    result->rest = rest;
    return result;
}

aio_result *new_aio_boo_result(const_boolean boolean_acc, str_hook *rest) {
    aio_result *result = new_object(sizeof(aio_result));
    result->value->boolean_acc = boolean_acc;
    result->rest = rest;
    return result;
}

void free_aio_result(aio_result *result) {

}