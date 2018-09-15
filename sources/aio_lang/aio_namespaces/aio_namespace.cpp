#include <aio_lang/aio_namespaces/aio_namespace_definition.h>

aio_namespace_definition::aio_namespace_definition(
        array_list<aio_class_definition> *class_definition_list,
        array_list<aio_scope_definition> *scope_definition_list,
        array_list<aio_function_definition> *function_definition_list,
        array_list<aio_field_definition> *field_definition_list
)
{
    this->class_definition_list = class_definition_list;
    this->scope_definition_list = scope_definition_list;
    this->function_definition_list = function_definition_list;
    this->field_definition_list = field_definition_list;
}

aio_namespace_definition::~aio_namespace_definition()
{
    //
    this->class_definition_list->free_elements();
    this->scope_definition_list->free_elements();
    this->function_definition_list->free_elements();
    this->field_definition_list->free_elements();
    //
    this->class_definition_list;
}
