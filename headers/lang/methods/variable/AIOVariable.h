#include "../../types/AIOType.h"

#ifndef AIO_AIO_VARIABLE_H
#define AIO_AIO_VARIABLE_H

typedef struct AIOVariable {
    char *name;
    char *value;
    int *mutable;
    enum AIOType *type;
} AIOVariable;

void createAIOVariable(AIOVariable **variable, char *name, char *value, int *mutable, enum AIOType *type);

#endif //AIO_AIO_VARIABLE_H