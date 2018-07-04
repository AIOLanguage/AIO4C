#include "../../lib/utils/string_utils/string_utils.h"

#ifndef AIO_ANNOTATION_H
#define AIO_ANNOTATION_H

typedef struct aio_annotation {
    const_string methodName;
    const_string annotationType;
} aio_annotation;

aio_annotation *new_aio_annotation(const_string methodName, const_string annotationType);

void delete_aio_annotation(aio_annotation *annotation);

#endif //AIO_ANNOTATION_H