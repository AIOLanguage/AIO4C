#include <aio_lang/aio_space/aio_file/aio_file.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook_list/str_hook_list.h>
#include <lib4aio_cpp_headers/utils/pair/aio_pair.h>

#define AIO_FILE_PARENT nullptr

#define AIO_FILE_ANNOTATION_LIST nullptr

using namespace lib4aio;

aio_file::aio_file(
        aio_pair<str_hook, char> *path_entry,
        const char *source_file,
        array_list<str_hook> *import_list,
        array_list<aio_class> *class_definition_list,
        array_list<aio_enum> *enum_definition_list,
        array_list<aio_scope> *scope_definition_list,
        array_list<aio_function> *function_definition_list,
        array_list<aio_field> *field_definition_list
) : aio_space(
        AIO_PUBLIC,
        AIO_FILE_PARENT,
        class_definition_list,
        enum_definition_list,
        scope_definition_list,
        function_definition_list,
        field_definition_list,
        AIO_FILE_ANNOTATION_LIST
)
{
    this->path_entry = path_entry;
    this->source_file = source_file;
    this->import_list = import_list;
}

aio_file::~aio_file()
{
    this->import_list->free_elements();
    delete this->path_entry;
    delete this->import_list;
    delete this->source_file;
}

const aio_pair<str_hook, char> * aio_file::get_path() const
{
    return this->path_entry;
}

const char *aio_file::get_source_file() const
{
    return this->source_file;
}

const array_list<str_hook> *aio_file::get_import_list() const
{
    return this->import_list;
}
