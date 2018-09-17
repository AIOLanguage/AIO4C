#include <aio_lang/aio_space/aio_initializable/aio_initializable.h>
#include <aio_lang/aio_invokable/aio_function/aio_function.h>
#include <aio_lang/aio_space/aio_scope/aio_scope.h>
#include <aio_lang/aio_space/aio_initializable/aio_enum/aio_enum.h>
#include <aio_lang/aio_space/aio_initializable/aio_class/aio_class.h>
#include <aio_lang/aio_space/aio_space.h>
#include <aio_lang/aio_visibility/aio_visibility.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>

aio_initializable::aio_initializable(
        aio_visibility visibility_type,
        aio_space *parent_namespace,
        array_list<aio_class> *class_definition_list,
        array_list<aio_enum> *enum_definition_list,
        array_list<aio_scope> *scope_definition_list,
        array_list<aio_function> *function_definition_list,
        array_list<aio_field> *field_definition_list,
        array_list<aio_class> *annotation_list,
        array_list<aio_constructor> *constructor_definition_list
) : aio_space(
        visibility_type,
        parent_namespace,
        class_definition_list,
        enum_definition_list,
        scope_definition_list,
        function_definition_list,
        field_definition_list,
        annotation_list
)
{
    this->constructor_definition_list = constructor_definition_list;
}

aio_initializable::~aio_initializable()
{
    this->constructor_definition_list->free_elements();
    delete this->constructor_definition_list;
}