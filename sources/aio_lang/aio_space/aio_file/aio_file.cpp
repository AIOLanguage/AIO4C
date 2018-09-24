#include <aio_lang/aio_space/aio_file/aio_file.h>
#include <lib4aio_cpp_headers/utils/str_builder/str_builder.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

#define AIO_FILE_PARENT nullptr

#define AIO_FILE_ANNOTATION_LIST nullptr

using namespace lib4aio;

aio_file::aio_file()
{}

aio_file::~aio_file()
{
    this->import_list->free_elements();
    delete this->relative_path;
    delete this->import_list;
    delete this->content;
}

const str_hook *aio_file::get_relative_path() const
{
    return this->relative_path;
}

const str_builder * aio_file::get_content() const
{
    return this->content;
}

const array_list<str_hook> *aio_file::get_imports() const
{
    return this->import_list;
}