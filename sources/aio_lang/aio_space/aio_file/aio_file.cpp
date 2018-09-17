#include <aio_lang/aio_space/aio_file/aio_file.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook_list/str_hook_list.h>

#define AIO_FILE_PARENT nullptr

#define AIO_FILE_ANNOTATION_LIST nullptr

using namespace lib4aio;

aio_file::aio_file(
        str_hook *path,
        const char *source_file,
        str_hook_chain *source_context,
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
    this->path = path;
    this->source_file = source_file;
    this->source_context = source_context;
    this->import_list = import_list;
}

aio_file::~aio_file()
{
    this->import_list->free_elements();
    delete this->path;
    delete this->import_list;
    delete this->source_context;
    delete this->source_file;
}

const str_hook *aio_file::get_path() const
{
    return this->path;
}

const char *aio_file::get_source_file() const
{
    return this->source_file;
}

const str_hook_chain *aio_file::get_source_context() const
{
    return this->source_context;
}

const array_list<str_hook> *aio_file::get_import_list() const
{
    return this->import_list;
}
