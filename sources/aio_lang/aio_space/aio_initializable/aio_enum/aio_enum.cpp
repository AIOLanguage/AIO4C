#include <aio_lang/aio_namespaces/aio_enum_definition/aio_enum_definition.h>

aio_enum_definition::aio_enum(
        aio_visibility_type visibility_type,
        aio_namespace_definition *parent_namespace,
        array_list<aio_class_definition> *class_definition_list,
        array_list<aio_enum_definition> *enum_definition_list,
        array_list<aio_scope_definition> *scope_definition_list,
        array_list<aio_function_definition> *function_definition_list,
        array_list<aio_field_definition> *field_definition_list,
        array_list<str_hook *> elements
) : aio_namespace_definition(
        visibility_type,
        parent_namespace,
        class_definition_list,
        enum_definition_list,
        scope_definition_list,
        function_definition_list,
        field_definition_list
)
{
    this->elements = elements;
}