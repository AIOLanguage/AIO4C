#ifndef AIO_FUNCTION_H
#define AIO_FUNCTION_H

#include <aio_lang/aio_invokable/aio_invokable.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

/**
 * 함수.
 */

class aio_function : aio_invokable {

private:

    str_hook *name;

    array_list<str_hook> *output_types;

public:

    aio_function(
            const unsigned arg_count,
            aio_invokable_circuit *root_circuit,
            str_hook *name,
            array_list<str_hook> *output_types,
            array_list<aio_class> *annotations
    );

    ~aio_function();

    const str_hook *get_name() const;

    const array_list<str_hook> *get_output_types() const;

};

#endif //AIO_FUNCTION_H