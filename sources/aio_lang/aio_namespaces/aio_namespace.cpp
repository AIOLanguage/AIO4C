#include <aio_lang/aio_namespaces/aio_namespace_definition.h>

aio_namespace_definition::aio_namespace_definition(
        aio_visibility_type visibility_type,
        aio_namespace_definition *parent_namespace,
        array_list<aio_class_definition> *class_definition_list,
        array_list<aio_scope_definition> *scope_definition_list,
        array_list<aio_function_definition> *function_definition_list,
        array_list<aio_field_definition> *field_definition_list
)
{
    this->visibility_type = visibility_type;
    this->parent_namespace = parent_namespace;
    this->class_definition_list = class_definition_list;
    this->scope_definition_list = scope_definition_list;
    this->function_definition_list = function_definition_list;
    this->field_definition_list = field_definition_list;
}

aio_namespace_definition::~aio_namespace_definition()
{
    //정의들을 청소하디
    this->class_definition_list->free_elements();
    this->scope_definition_list->free_elements();
    this->function_definition_list->free_elements();
    this->field_definition_list->free_elements();
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기:
    delete this->class_definition_list;
    delete this->scope_definition_list;
    delete this->function_definition_list;
    delete this->field_definition_list;
}

const aio_visibility_type aio_namespace_definition::get_visibility_type() const
{
    return this->visibility_type;
}

const array_list<aio_class_definition> *aio_namespace_definition::get_class_definition_list() const
{
    return this->class_definition_list;
}

const array_list<aio_scope_definition> *aio_namespace_definition::get_scope_definition_list() const
{
    return this->scope_definition_list;
}

const array_list<aio_function_definition> *aio_namespace_definition::get_function_definition_list() const
{
    return this->function_definition_list;
}

const array_list<aio_field_definition> *aio_namespace_definition::get_field_definition_list() const
{
    return this->field_definition_list;
}
