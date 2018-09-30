//lang:
#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_space/aio_file/aio_file.h>
#include <aio_lang/aio_space/aio_scope/aio_scope.h>
#include <aio_lang/aio_invokable/aio_function/aio_function.h>
#include <aio_lang/aio_space/aio_initializable/aio_class/aio_class.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/str_builder/str_builder.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

#define AIO_FILE_PARENT nullptr

using namespace lib4aio;

aio_file::aio_file(str_builder *content, const str_hook *relative_file_path)
{
    this->parent = AIO_FILE_PARENT;
    this->visibility_type = AIO_VISIBILITY_PUBLIC;
    this->content = content;
    this->relative_path = relative_file_path;
    this->marknames = new array_list<aio_class>();
    this->functions = new array_list<aio_function>();
    this->pathnames = new array_list<aio_scope>();
    this->typenames = new array_list<aio_class>();
    this->fields = new array_list<aio_field>();
    this->additions = new array_list<str_hook>();
}

aio_file::~aio_file()
{
    this->additions->free_elements();
    delete this->relative_path;
    delete this->additions;
    delete this->content;
}