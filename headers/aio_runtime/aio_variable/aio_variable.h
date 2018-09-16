#ifndef AIO_VARIABLE_H
#define AIO_VARIABLE_H

/**
 * Variabe.
 */

class aio_variable {

    class aio_field_definition *definition;

    struct aio_value *value;

    enum {
        AIO_FIELD_NOT_INITIALIZED, AIO_FIELD_INITIALIZED
    } init_type;
};

#endif //AIO_VARIABLE_H