#ifndef AIO_FUNCTION_H
#define AIO_FUNCTION_H

/**
 * 연결.
 */

#include <aio_lang/aio_invokable/aio_invokable.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <aio_lang/aio_inheritable/aio_inheritable.h>

/**
 * 함수.
 */

class aio_function : aio_invokable, public aio_inheritable<aio_function>{

public:

    explicit aio_function(
            const unsigned arg_count,
            aio_invokable_circuit *root_circuit,
            str_hook *name,
            array_list<str_hook> *output_types,
            array_list<aio_class> *annotations,
            array_list<aio_function> *parents,
            aio_inherited_type inherited_type
    );

    ~aio_function();

    const str_hook *get_name() const;

private:

    str_hook *name;
};

#endif //AIO_FUNCTION_H