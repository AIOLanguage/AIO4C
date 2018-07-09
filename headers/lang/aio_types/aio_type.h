#ifndef AIO_TYPE_H
#define AIO_TYPE_H

#include "../../lib/utils/string_utils/string_utils.h"
#include "../../lib/utils/boolean_utils/boolean_utils.h"

#define VOID "Voi"

enum aio_type {
    AIO_INT, AIO_DOU, AIO_STR, AIO_VOI
};

void set_aio_type(const_string, enum aio_type *type);

boolean is_aio_int_type(enum aio_type type);

boolean is_aio_dou_type(enum aio_type type);

boolean is_aio_str_type(enum aio_type type);

string int_to_str(int src);

string double_to_str(double src);

#endif //AIO_TYPE_H