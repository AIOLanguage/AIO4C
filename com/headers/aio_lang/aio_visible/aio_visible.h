#ifndef AIO_VISIBLE_H
#define AIO_VISIBLE_H

class aio_visible {

public:

    enum {
        AIO_VISIBILITY_UNDEFINED,
        AIO_VISIBILITY_LOCAL,
        AIO_VISIBILITY_PRIVATE,
        AIO_VISIBILITY_PROTECTED,
        AIO_VISIBILITY_PUBLIC
    } visibility;

    aio_visible();

    bool is_local_field();

    bool is_private_field();

    bool is_protected_field();

    bool is_internal_field();

    bool is_public_field();

    virtual ~aio_visible();

    void log_aio_visibility() const ;

    bool operator==(const aio_visible &rhs) const;
};

#endif //AIO_VISIBLE_H