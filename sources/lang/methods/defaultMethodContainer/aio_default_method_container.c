#include <mem.h>
#include <math.h>
#include <comip.h>
#include "../../../../headers/lang/methods/result/aio_result.h"

int is_default_int_method(char *method_name, aio_int_result *result) {
    if (strcmp(method_name, "pp") == 0) {
        *result->acc = *result->acc + 1;
        return 0;
    } else if (strcmp(method_name, "mm") == 0){
        *result->acc = *result->acc - 1;
        return 0;
    } else return -1;
}

int is_default_dou_method(char *method_name, aio_dou_result *result) {
    if (strcmp(method_name, "sin") == 0) {
        *result->acc = sin(*result->acc);
        return 0;
    } else if (strcmp(method_name, "cos") == 0) {
        *result->acc = cos(*result->acc);
        return 0;
    } else if (strcmp(method_name, "tan") == 0) {
        *result->acc = tan(*result->acc);
        return 0;
    } else if (strcmp(method_name, "sqr") == 0){
        *result->acc = *result->acc * *result->acc;
        return 0;
    } else if (strcmp(method_name, "sqrt") == 0){
        *result->acc = sqrt(*result->acc);
        return 0;
    } else return -1;
}

int is_default_cha_method(char *methodName, aio_cha_result *result) {

}

int is_default_str_method(char *methodName, aio_str_result *result) {

}