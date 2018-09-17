#include <aio_lang/aio_space/aio_initializable/aio_enum/aio_enum.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>

using namespace lib4aio;

aio_enum::aio_enum(
        aio_visibility visibility_type,
        aio_space *parent,
        array_list<aio_class> *class_definition_list,
        array_list<aio_enum> *enum_definition_list,
        array_list<aio_scope> *scope_definition_list,
        array_list<aio_function> *function_definition_list,
        array_list<aio_field> *field_definition_list,
        array_list<aio_class> *annotation_list,
        array_list<aio_constructor> *constructor_definition_list,
        array_list<aio_field> *elements
) : aio_initializable(
        visibility_type,
        parent,
        class_definition_list,
        enum_definition_list,
        scope_definition_list,
        function_definition_list,
        field_definition_list,
        annotation_list,
        constructor_definition_list
)
{
    this->elements = elements;
}

aio_enum::~aio_enum()
{
    this->elements->free_elements();
    delete this->elements;
}

const array_list<aio_field> *aio_enum::get_values() const
{
    return this->elements;
}
