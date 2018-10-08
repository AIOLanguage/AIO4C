#ifndef AIO_VISIBILITY_H
#define AIO_VISIBILITY_H

struct aio_field;

typedef enum aio_visibility {
    AIO_VISIBILITY_UNDEFINED,
    AIO_VISIBILITY_LOCAL,
    AIO_VISIBILITY_PRIVATE,
    AIO_VISIBILITY_PROTECTED,
    AIO_VISIBILITY_PUBLIC
} aio_visibility;

bool is_local_field(const aio_field *field);

bool is_private_field(const aio_field *field);

bool is_protected_field(const aio_field *field);

bool is_internal_field(const aio_field *field);

bool is_public_field(const aio_field *field);

#endif //AIO_VISIBILITY_H