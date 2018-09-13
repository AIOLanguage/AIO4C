#ifndef AIO_FIELD_DEFINITION_H
#define AIO_FIELD_DEFINITION_H

#include <aio_lang/aio_visibility_type/aio_visibility_type.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

using namespace lib4aio;

class aio_field_definition
{

private:

    str_hook *name;

    str_hook *type;

    bool is_array;

    bool is_mutable;

    aio_visibility_type visibility_type;

public:

};

#endif //AIO_FIELD_DEFINITION_H
