#include <aio_lang/aio_space/aio_file/aio_file.h>
#include <lib4aio_cpp_headers/utils/str_builder/str_builder.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

#define AIO_FILE_PARENT nullptr

#define AIO_FILE_ANNOTATION_LIST nullptr

using namespace lib4aio;

aio_file::aio_file(str_builder *file_content, const str_hook *relative_file_path)
{
    this->parent_namespace = AIO_FILE_PARENT;
    this->annotation_definition_list = AIO_FILE_ANNOTATION_LIST;
    this->relative_path = relative_file_path;
    this->content = file_content;
}

aio_file::~aio_file()
{
    this->import_list->free_elements();
    delete this->relative_path;
    delete this->import_list;
    delete this->content;
}