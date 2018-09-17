#ifndef AIO_SCOPE_H
#define AIO_SCOPE_H

/**
 * 연결.
 */

#include <aio_lang/aio_space/aio_space.h>

class aio_scope : aio_space {

public:

    explicit aio_scope(
            aio_visibility visibility_type,
            aio_space *parent_namespace,
            array_list<aio_class> *class_definition_list,
            array_list<aio_enum> *enum_definition_list,
            array_list<aio_scope> *scope_definition_list,
            array_list<aio_function> *function_definition_list,
            array_list<aio_field> *field_definition_list
    );

    ~aio_scope();

    const array_list<aio_class> *get_annotation_definition_list() const = delete;
};

#endif //AIO_SCOPE_H