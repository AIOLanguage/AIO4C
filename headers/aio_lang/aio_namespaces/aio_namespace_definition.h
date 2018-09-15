#ifndef AIO_NAMESPACE_H
#define AIO_NAMESPACE_H

/**
 * 연결.
 */

#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <aio_lang/aio_file/aio_function/definition/aio_function_definition.h>
#include <aio_lang/aio_file/aio_field/definition/aio_field_definition.h>
#include <aio_lang/aio_file/aio_class_definition/aio_class_definiiton.h>
#include <aio_lang/aio_namespaces/aio_scope/aio_scope_definition.h>

using namespace lib4aio;

class aio_namespace_definition {

private:

    array_list<aio_class_definition> *class_definition_list;

    array_list<aio_scope_definition> *scope_definition_list;

    array_list<aio_function_definition> *function_definition_list;

    array_list<aio_field_definition> *field_definition_list;

public:

    explicit aio_namespace_definition(
            array_list<aio_class_definition> *class_definition_list,
            array_list<aio_scope_definition> *scope_definition_list,
            array_list<aio_function_definition> *function_definition_list,
            array_list<aio_field_definition> *field_definition_list
    );

    explicit ~aio_namespace_definition();

    const array_list<aio_class_definition> *get_class_definition_list() const;

    const array_list<aio_scope_definition> *get_scope_definition_list() const;

    const array_list<aio_function_definition> *get_function_definition_list() const;

    const array_list<aio_field_definition> *get_field_definition_list() const;
};

#endif //AIO_NAMESPACE_H