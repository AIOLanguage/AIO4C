#include <mem.h>
#include <math.h>
#include <comip.h>
#include "../../../../headers/lang/methods/result/AIOResult.h"

int isDefaultIntMethod(char *methodName, AIOIntResult *result) {
    if (strcmp(methodName, "pp") == 0) {
        *result->acc = *result->acc + 1;
        return 0;
    } else if (strcmp(methodName, "mm") == 0){
        *result->acc = *result->acc - 1;
        return 0;
    } else return -1;
}

int isDefaultDouMethod(char *methodName, AIODouResult *result) {
    if (strcmp(methodName, "sin") == 0) {
        *result->acc = sin(*result->acc);
        return 0;
    } else if (strcmp(methodName, "cos") == 0) {
        *result->acc = cos(*result->acc);
        return 0;
    } else if (strcmp(methodName, "tan") == 0) {
        *result->acc = tan(*result->acc);
        return 0;
    } else if (strcmp(methodName, "sqr") == 0){
        *result->acc = *result->acc * *result->acc;
        return 0;
    } else if (strcmp(methodName, "sqrt") == 0){
        *result->acc = sqrt(*result->acc);
        return 0;
    } else return -1;
}

int isDefaultChaMethod(char *methodName, AIOChaResult* result) {

}

int isDefaultStrMethod(char *methodName, AIOStrResult* result) {

}