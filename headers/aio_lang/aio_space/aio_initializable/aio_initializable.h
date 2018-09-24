#ifndef AIO_INITIALIZABLE_H
#define AIO_INITIALIZABLE_H

/**
 * 연결.
 */

#include <aio_lang/aio_space/aio_space.h>
#include <aio_lang/aio_visibility/aio_visibility.h>

class aio_constructor;

class aio_initializable : public aio_space {

public:

    explicit aio_initializable();

    virtual ~aio_initializable();

protected:

    array_list<aio_constructor> *constructor_definition_list;
};

#endif //AIO_INITIALIZABLE_H