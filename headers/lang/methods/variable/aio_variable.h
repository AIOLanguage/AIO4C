#include "../../types/aio_type.h"

#ifndef AIO_AIO_VARIABLE_H
#define AIO_AIO_VARIABLE_H

typedef struct aio_variable {
    char *name;
    char *value;
    int *mutable;
    enum aio_type *type;
} aio_variable;

aio_variable* new_aio_variable(char *name, char *value, int mutable, enum aio_type *type);

#endif //AIO_AIO_VARIABLE_H