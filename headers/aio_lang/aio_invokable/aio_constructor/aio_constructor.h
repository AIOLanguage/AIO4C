#ifndef AIO_CONSTRUCTOR_H
#define AIO_CONSTRUCTOR_H

/**
 * 연결.
 */

#include <aio_lang/aio_invokable/aio_invokable.h>
#include <aio_lang/aio_inheritable/aio_inheritable.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

class aio_constructor : aio_invokable, aio_inheritable<aio_constructor> {

    aio_constructor(
            const unsigned arg_count,
            aio_invokable_circuit *root_circuit,
            array_list<str_hook> *output_types,
            array_list<aio_class> *annotations,
            array_list<aio_constructor> *parents
    );
};

#endif //AIO_CONSTRUCTOR_H