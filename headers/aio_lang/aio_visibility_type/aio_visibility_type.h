#ifndef AIO_SCOPE_H
#define AIO_SCOPE_H

typedef enum aio_visibility_type {
    AIO_LOCAL, AIO_PRIVATE, AIO_PROTECTED, AIO_INTERNAL, AIO_PUBLIC
} aio_visibility_type;

_Bool is_local_field(struct aio_field *field);

_Bool is_private_field(struct aio_field *field);

_Bool is_protected_field(struct aio_field *field);

_Bool is_internal_field(struct aio_field *field);

_Bool is_public_field(struct aio_field *field);

#endif //AIO_SCOPE_H