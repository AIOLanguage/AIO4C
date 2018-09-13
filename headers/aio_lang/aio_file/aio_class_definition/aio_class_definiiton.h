#ifndef AIO_CLASS_DEFINITION_H
#define AIO_CLASS_DEFINITION_H

#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>

using namespace lib4aio;

/**
 * Class.
 */

class aio_class_definition
{

private:
    array_list<aio_class_definition> annotation_definitions;

    array_list<aio_class_definition> parent_definitions;

    array_list<aio_field_definition> field_definitions;

    array_list<aio_function_definition> function_definitions;
public:

};

#endif //AIO_CLASS_DEFINITION_H