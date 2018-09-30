#ifndef AIO_SPACE_H
#define AIO_SPACE_H

/**
 * 연결.
 */

#include <aio_lang/aio_visibility/aio_visibility.h>
#include <aio_lang/aio_annotatable/aio_annotatable.h>
#include <aio_lang/aio_schemable/aio_schemable.h>

class aio_enum;

class aio_scope;

class aio_function;

class aio_field;

class aio_space : public aio_annotatable, public aio_schemable<aio_space> {

public:

    explicit aio_space();

    virtual ~aio_space();

    aio_visibility visibility_type;

    aio_space *parent;

    array_list<aio_class> *typenames;

    array_list<aio_enum> *enum_definition_list;

    array_list<aio_scope> *pathnames;

    array_list<aio_function> *functions;
};

#endif //AIO_SPACE_H