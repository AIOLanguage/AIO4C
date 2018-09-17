#include <aio_lang/aio_space/aio_initializable/aio_class/aio_class.h>
#include <aio_lang/aio_inheritable/aio_inheritable.cpp>

aio_class::aio_class(
        aio_visibility visibility_type,
        aio_space *parent_namespace,
        array_list<aio_class> *class_definition_list,
        array_list<aio_enum> *enum_definition_list,
        array_list<aio_scope> *scope_definition_list,
        array_list<aio_function> *function_definition_list,
        array_list<aio_field> *field_definition_list,
        array_list<aio_class> *annotation_list,
        array_list<aio_constructor> *constructor_definition_list,
        array_list<aio_class> *parent_classes,
        aio_inherited_type inherited_type
) : aio_initializable(
        visibility_type,
        parent_namespace,
        class_definition_list,
        enum_definition_list,
        scope_definition_list,
        function_definition_list,
        field_definition_list,
        annotation_list,
        constructor_definition_list
), aio_inheritable(
        parent_classes,
        inherited_type
)
{}

aio_class::~aio_class()
{}