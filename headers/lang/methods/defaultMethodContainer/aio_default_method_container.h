#ifndef AIO_DEFAULT_METHOD_CONTAINER_H
#define AIO_DEFAULT_METHOD_CONTAINER_H

#include "../result/aio_result.h"

int is_default_int_method(char *method_name, aio_int_result *result);

int is_default_dou_method(char *method_name, aio_dou_result *result);

int is_default_cha_method(char *method_name, aio_cha_result *result);

int is_default_str_method(char *method_name, aio_str_result *result);

#endif //AIO_DEFAULT_METHOD_CONTAINER_H