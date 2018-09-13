#ifndef AIO_SOURCE_FILE_H
#define AIO_SOURCE_FILE_H

#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook_list/str_hook_list.h>

using namespace lib4aio;

typedef struct aio_file
{
private:

    str_hook *path;

    const char * source_file;

    str_hook_chain *source_context;

    /**
     * Content.
     */

    array_list<str_hook> *import_list;

    array_list<aio_function_definition> *global_function_definition_list;

    array_list<aio_field_definition> *global_field_definition_list;

    array_list<aio_class_definition> *class_list;
public:

} aio_source_file;

#endif //AIO_SOURCE_FILE_H