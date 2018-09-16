#ifndef AIO_CONSTRUCTOR_H
#define AIO_CONSTRUCTOR_H

#include <aio_lang/aio_invokable/aio_invokable.h>

class aio_constructor : aio_invokable {

    aio_constructor(
            const unsigned arg_count,
            aio_invokable_circuit *root_circuit,
            str_hook *class_name,
            array_list<aio_class> *annotations
    ) : aio_invokable(arg_count, root_circuit, annotations)
    {

    }
};

#endif //AIO_CONSTRUCTOR_H