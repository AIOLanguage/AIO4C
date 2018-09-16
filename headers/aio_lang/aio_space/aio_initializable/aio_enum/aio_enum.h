#ifndef AIO_ENUM_DEFINITION_H
#define AIO_ENUM_DEFINITION_H

#include <aio_lang/aio_namespaces/aio_space_definition.h>
#include <aio_utils/aio_value/aio_value.h>

class aio_enum : aio_space_definition {

    array_list<str_hook *> elements;

    explicit aio_enum(
            aio_visibility_type visibility_type,
            aio_space_definition *parent_namespace,
            array_list<aio_class_definition> *class_definition_list,
            array_list<aio_enum> *enum_definition_list,
            array_list<aio_scope_definition> *scope_definition_list,
            array_list<aio_function_definition> *function_definition_list,
            array_list<aio_field_definition> *field_definition_list,
            array_list<str_hook *> elements
    );

    ~aio_enum();

    const array_list<str_hook *> get_values() const;
};

#endif //AIO_ENUM_DEFINITION_H