#ifndef AIO_SCOPE_H
#define AIO_SCOPE_H

#include <aio_lang/aio_namespaces/aio_space_definition.h>

class aio_scope : aio_space_definition {

public:

    aio_scope(
            aio_visibility_type visibility_type,
            aio_space_definition *parent_namespace,
            array_list<aio_class_definition> *class_definition_list,
            array_list<aio_scope> *scope_definition_list,
            array_list<aio_function_definition> *function_definition_list,
            array_list<aio_field_definition> *field_definition_list
    );

};

#endif //AIO_SCOPE_H