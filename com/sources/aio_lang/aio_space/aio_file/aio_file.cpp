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

using namespace lib4aio;

aio_file::aio_file(str_builder *content, const char *absolute_file_path)
{
    this->visibility = AIO_VISIBILITY_PUBLIC;
    this->content = content;
    this->absolute_path = absolute_file_path;
    this->additions = new array_list<str_hook>(true);
}

aio_file::~aio_file()
{
    delete this->absolute_path;
    delete this->additions;
    delete this->content;
}