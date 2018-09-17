#include <aio_lang/aio_space/aio_scope/aio_scope.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>

#define AIO_SCOPE_ANNOTATION_LIST nullptr

aio_scope::aio_scope(
        aio_visibility visibility_type,
        aio_space *parent_namespace,
        array_list<aio_class> *class_definition_list,
        array_list<aio_enum> *enum_definition_list,
        array_list<aio_scope> *scope_definition_list,
        array_list<aio_function> *function_definition_list,
        array_list<aio_field> *field_definition_list
) : aio_space(
        visibility_type,
        parent_namespace,
        class_definition_list,
        enum_definition_list,
        scope_definition_list,
        function_definition_list,
        field_definition_list,
        AIO_SCOPE_ANNOTATION_LIST
)
{}

aio_scope::~aio_scope()
{}
