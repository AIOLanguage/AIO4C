#ifndef AIO_INVOKABLE_H
#define AIO_INVOKABLE_H

#include <aio_lang/aio_annotatable/aio_annotatable.h>
#include <aio_parsing/aio_invokable_circuit/aio_invokable_circuit.h>

/**
 * Overloading only by param count!!!
 */

class aio_invokable : aio_annotatable {

private:

    unsigned arg_count;

    aio_invokable_circuit *root_circuit;

public:

    explicit aio_invokable(
            const unsigned arg_count,
            aio_invokable_circuit *root_holder,
            array_list<aio_class> *annotations
    );

    virtual ~aio_invokable();

    const unsigned get_arg_count() const;

    const aio_invokable_circuit *get_root_circuit() const;
};

#endif //AIO_INVOKABLE_H