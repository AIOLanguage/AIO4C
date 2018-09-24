#ifndef AIO_SCHEMABLE_H
#define AIO_SCHEMABLE_H

class aio_scheme;

class aio_schemable {

public:

    aio_schemable();

    virtual ~aio_schemable();

    aio_scheme *get_scheme() const;

protected:

    aio_scheme *scheme;
};

#endif //AIO_SCHEMABLE_H