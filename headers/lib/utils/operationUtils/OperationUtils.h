#ifndef AIO_OPERATION_UTILS_H
#define AIO_OPERATION_UTILS_H

#include <mem.h>

int is_plus_operation(char *string);

int is_multiply_operation(char *string);

int is_concat_operation(char *string);

int isDefaultOperations(const char* string);

#endif //AIO_OPERATION_UTILS_H