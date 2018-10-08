//lang:
#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_schemable/aio_schemable.h>
//runtime:
#include <aio_runtime/aio_task/aio_task.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>

aio_schemable::aio_schemable()
{
    this->instructions = new array_list<aio_task>();
    this->fields = new array_list<aio_field>();
}

aio_schemable::~aio_schemable()
{
    this->instructions->free_elements();
    this->fields->free_elements();
    delete this->instructions;
    delete this->fields;
}