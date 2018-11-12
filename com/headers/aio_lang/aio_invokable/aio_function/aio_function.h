#ifndef AIO_FUNCTION_H
#define AIO_FUNCTION_H

/**
 * 연결.
 */

//lang:
#include <aio_lang/aio_invokable/aio_invokable.h>
#include <aio_lang/aio_inheritable/aio_inheritable.h>

struct aio_function : public aio_invokable, public aio_inheritable<aio_function> {

    str_hook *name;

    explicit aio_function();

    ~aio_function();

    bool operator==(const aio_function &rhs) const;

    bool operator!=(const aio_function &rhs) const;

    bool compare(const aio_function *o1, const aio_function *o2) const;

    static bool compare_functions(const aio_function *o1, const aio_function *o2);
};

#endif //AIO_FUNCTION_H