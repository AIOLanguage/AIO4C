#ifndef AIO_VARIABLE_H
#define AIO_VARIABLE_H

/**
 * Variable.
 */

struct aio_field;

struct aio_value;

struct aio_variable {

    explicit aio_variable();

    ~aio_variable();

    aio_field *definition;

    aio_value *value;

    enum {
        AIO_FIELD_NOT_INITIALIZED, AIO_FIELD_INITIALIZED
    } init_type;
};

#endif //AIO_VARIABLE_H