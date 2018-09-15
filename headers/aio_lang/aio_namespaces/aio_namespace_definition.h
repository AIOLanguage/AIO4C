#ifndef AIO_NAMESPACE_H
#define AIO_NAMESPACE_H

#include <aio_lang/aio_visibility_type/aio_visibility_type.h>
#include <aio_lang/aio_file/aio_class_definition/aio_class_definiiton.h>
#include <aio_lang/aio_file/aio_field/definition/aio_field_definition.h>
#include <aio_lang/aio_file/aio_function/definition/aio_function_definition.h>

/**
 * 연결.
 */

class array_list;

class aio_scope_definition;

class aio_namespace_definition {

private:

    aio_visibility_type visibility_type;

    aio_namespace_definition *parent_namespace;

    array_list<aio_class_definition> *class_definition_list;

    array_list<aio_scope_definition> *scope_definition_list;

    array_list<aio_function_definition> *function_definition_list;

    array_list<aio_field_definition> *field_definition_list;

public:

    explicit aio_namespace_definition(
            aio_visibility_type visibility_type,
            aio_namespace_definition *parent_namespace,
            array_list<aio_class_definition> *class_definition_list,
            array_list<aio_scope_definition> *scope_definition_list,
            array_list<aio_function_definition> *function_definition_list,
            array_list<aio_field_definition> *field_definition_list
    );

    ~aio_namespace_definition();

    const aio_visibility_type get_visibility_type() const;

    const array_list<aio_class_definition> *get_class_definition_list() const;

    const array_list<aio_scope_definition> *get_scope_definition_list() const;

    const array_list<aio_function_definition> *get_function_definition_list() const;

    const array_list<aio_field_definition> *get_field_definition_list() const;
};

#endif //AIO_NAMESPACE_H