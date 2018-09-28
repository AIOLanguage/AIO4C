#ifndef AIO_VARIABLE_H
#define AIO_VARIABLE_H

/**
 * Variable.
 */


class aio_field;

struct aio_value;

class aio_variable {

public:

    explicit aio_variable();

    ~aio_variable();

    aio_value *get_value();

    const aio_field *get_definition() const;

private:

    aio_field *definition;

    aio_value *value;

    enum {
        AIO_FIELD_NOT_INITIALIZED, AIO_FIELD_INITIALIZED
    } init_type;
};

#endif //AIO_VARIABLE_H