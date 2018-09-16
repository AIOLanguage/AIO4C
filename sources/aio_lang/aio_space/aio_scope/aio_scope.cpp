#include <aio_lang/aio_namespaces/aio_scope/aio_scope_definition.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>

aio_scope_definition::aio_scope(
        aio_visibility_type visibility_type,
        aio_space_definition *parent_namespace,
        array_list<aio_class_definition> *class_definition_list,
        array_list<aio_scope_definition> *scope_definition_list,
        array_list<aio_function_definition> *function_definition_list,
        array_list<aio_field_definition> *field_definition_list
) : aio_space_definition(
        visibility_type,
        parent_namespace,
        class_definition_list,
        scope_definition_list,
        function_definition_list,
        field_definition_list
)
{
}