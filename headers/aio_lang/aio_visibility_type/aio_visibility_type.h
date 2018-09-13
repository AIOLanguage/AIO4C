#ifndef AIO_VISIBILITY_TYPE_H
#define AIO_VISIBILITY_TYPE_H

typedef enum aio_visibility_type {
    AIO_LOCAL, AIO_PRIVATE, AIO_PROTECTED, AIO_INTERNAL, AIO_PUBLIC
} aio_visibility_type;

/**
 * Class.
 */

/**
 * Field.
 */

bool is_local_field(aio_field *field);

bool is_private_field(aio_field *field);

bool is_protected_field(aio_field *field);

bool is_internal_field(aio_field *field);

bool is_public_field(aio_field *field);

#endif //AIO_VISIBILITY_TYPE_H