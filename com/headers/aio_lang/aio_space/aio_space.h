#ifndef AIO_SPACE_H
#define AIO_SPACE_H

/**
 * 연결.
 */

//lang:
#include <aio_lang/aio_schemable/aio_schemable.h>
#include <aio_lang/aio_visibility/aio_visibility.h>
#include <aio_lang/aio_annotatable/aio_annotatable.h>

struct aio_enum;

struct aio_scope;

struct aio_function;

struct aio_field;

struct aio_space : public aio_annotatable, public aio_schemable {

    explicit aio_space();

    virtual ~aio_space();

    aio_visibility visibility_type;

    array_list<aio_class> *typenames;

    array_list<aio_enum> *enumnames;

    array_list<aio_scope> *pathnames;

    array_list<aio_function> *functions;
};

#endif //AIO_SPACE_H