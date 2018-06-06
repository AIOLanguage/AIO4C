#ifndef AIO_DEFAULT_METHOD_CONTAINER_H
#define AIO_DEFAULT_METHOD_CONTAINER_H

#include "../result/AIOResult.h"

int isDefaultIntMethod(char* methodName, AIOIntResult* result);

int isDefaultDouMethod(char* methodName, AIODouResult* result);

int isDefaultChaMethod(char* methodName, AIOChaResult* result);

int isDefaultStrMethod(char* methodName, AIOStrResult* result);

#endif //AIO_DEFAULT_METHOD_CONTAINER_H