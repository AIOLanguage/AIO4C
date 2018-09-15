#ifndef AIO_SCOPE_DEFINITION_H
#define AIO_SCOPE_DEFINITION_H

#include <aio_lang/aio_namespaces/aio_namespace_definition.h>

class aio_scope_definition : aio_namespace_definition {

public:

    aio_scope_definition(
            aio_visibility_type visibility_type,
            aio_namespace_definition *parent_namespace,
            array_list<aio_class_definition> *class_definition_list,
            array_list<aio_scope_definition> *scope_definition_list,
            array_list<aio_function_definition> *function_definition_list,
            array_list<aio_field_definition> *field_definition_list
    );

};

#endif //AIO_SCOPE_DEFINITION_H