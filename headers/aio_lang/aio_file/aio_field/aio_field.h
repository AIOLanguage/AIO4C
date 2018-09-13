#ifndef AIO_FIELD_H
#define AIO_FIELD_H

/**
 * Field.
 */

class aio_filed
{

    class aio_field_definition *definition;

    struct aio_value *value;

    enum
    {
        AIO_FIELD_NOT_INITIALIZED, AIO_FIELD_INITIALIZED
    } init_type;
};

#endif //AIO_FIELD_H