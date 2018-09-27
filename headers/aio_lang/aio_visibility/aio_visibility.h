#ifndef AIO_VISIBILITY_H
#define AIO_VISIBILITY_H

class aio_field;

typedef enum aio_visibility {
    AIO_VISIBILITY_UNDEFINED,
    AIO_VISIBILITY_LOCAL,
    AIO_VISIBILITY_PRIVATE,
    AIO_VISIBILITY_PROTECTED,
    AIO_VISIBILITY_PUBLIC
} aio_visibility;

bool is_local_field(aio_field *field);

bool is_private_field(aio_field *field);

bool is_protected_field(aio_field *field);

bool is_internal_field(aio_field *field);

bool is_public_field(aio_field *field);

#endif //AIO_VISIBILITY_H