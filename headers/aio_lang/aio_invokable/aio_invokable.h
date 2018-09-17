#ifndef AIO_INVOKABLE_H
#define AIO_INVOKABLE_H

/**
 * 연결.
 */

#include <aio_lang/aio_annotatable/aio_annotatable.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

class aio_invokable_circuit;

/**
 * Overloading only by param count!!!
 */

class aio_invokable : aio_annotatable {

public:

    explicit aio_invokable(
            const unsigned arg_count,
            aio_invokable_circuit *root_circuit,
            array_list<str_hook> *output_types,
            array_list<aio_class> *annotations
    );

    virtual ~aio_invokable();

    const unsigned get_arg_count() const;

    const aio_invokable_circuit *get_root_circuit() const;

    const array_list<str_hook> *get_output_types() const;

private:

    unsigned arg_count;

    aio_invokable_circuit *root_circuit;

    array_list<str_hook> *output_types;
};

#endif //AIO_INVOKABLE_H