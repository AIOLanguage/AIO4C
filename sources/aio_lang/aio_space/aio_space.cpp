#include <aio_lang/aio_space/aio_space.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>

using namespace lib4aio;

aio_space::aio_space(
        aio_visibility visibility_type,
        aio_space *parent_namespace,
        array_list<aio_class> *class_definition_list,
        array_list<aio_enum> *enum_definition_list,
        array_list<aio_scope> *scope_definition_list,
        array_list<aio_function> *function_definition_list,
        array_list<aio_field> *field_definition_list,
        array_list<aio_class> *annotations
) : aio_annotatable(annotations)
{
    this->visibility_type = visibility_type;
    this->parent_namespace = parent_namespace;
    this->class_definition_list = class_definition_list;
    this->enum_definition_list = enum_definition_list;
    this->scope_definition_list = scope_definition_list;
    this->function_definition_list = function_definition_list;
    this->field_definition_list = field_definition_list;
}

aio_space::~aio_space()
{
    //정의들을 청소하디
    this->class_definition_list->free_elements();
    this->enum_definition_list->free_elements();
    this->scope_definition_list->free_elements();
    this->function_definition_list->free_elements();
    this->field_definition_list->free_elements();
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기:
    delete this->class_definition_list;
    delete this->enum_definition_list;
    delete this->scope_definition_list;
    delete this->function_definition_list;
    delete this->field_definition_list;
}

const aio_visibility aio_space::get_visibility_type() const
{
    return this->visibility_type;
}

const array_list<aio_class> *aio_space::get_class_definition_list() const
{
    return this->class_definition_list;
}

const array_list<aio_scope> *aio_space::get_scope_definition_list() const
{
    return this->scope_definition_list;
}

const array_list<aio_function> *aio_space::get_function_definition_list() const
{
    return this->function_definition_list;
}

const array_list<aio_field> *aio_space::get_field_definition_list() const
{
    return this->field_definition_list;
}

const aio_space *aio_space::get_parent_namespace() const
{
    return this->parent_namespace;
}

const array_list<aio_enum> *aio_space::get_enum_definition_list() const
{
    return this->enum_definition_list;
}
