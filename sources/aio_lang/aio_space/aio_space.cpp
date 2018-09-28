//lang:
#include <aio_lang/aio_space/aio_space.h>
#include <aio_lang/aio_schemable/aio_schemable.cpp>
//lib4aio:
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>

using namespace lib4aio;

aio_space::aio_space()
{}

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