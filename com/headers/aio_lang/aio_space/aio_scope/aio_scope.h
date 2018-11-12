#ifndef AIO_SCOPE_H
#define AIO_SCOPE_H

/**
 * 연결.
 */

//lang:
#include <aio_lang/aio_space/aio_space.h>

struct aio_scope : public aio_space {

    explicit aio_scope();

    ~aio_scope();

    str_hook *name;

    static bool compare_scopes(const aio_scope *o1, const aio_scope *o2);

    bool operator==(const aio_scope &rhs) const;

    bool operator!=(const aio_scope &rhs) const;
};

#endif //AIO_SCOPE_H