#ifndef AIO_SCOPE_H
#define AIO_SCOPE_H

/**
 * 연결.
 */

#include <aio_lang/aio_space/aio_space.h>

class aio_scope : public aio_space {

public:

    explicit aio_scope();

    ~aio_scope();

    const array_list<aio_class> *get_annotation_definition_list() const = 0;
};

#endif //AIO_SCOPE_H