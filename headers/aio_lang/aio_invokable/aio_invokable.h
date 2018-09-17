#ifndef AIO_INVOKABLE_H
#define AIO_INVOKABLE_H

#include <aio_lang/aio_annotatable/aio_annotatable.h>

class aio_invokable_circuit;

/**
 * Overloading only by param count!!!
 */

class aio_invokable : aio_annotatable {

public:

    explicit aio_invokable(
            const unsigned arg_count,
            aio_invokable_circuit *root_circuit,
            array_list<aio_class> *annotations
    );

    virtual ~aio_invokable();

    const unsigned get_arg_count() const;

    const aio_invokable_circuit *get_root_circuit() const;

private:

    unsigned arg_count;

    aio_invokable_circuit *root_circuit;

};

#endif //AIO_INVOKABLE_H