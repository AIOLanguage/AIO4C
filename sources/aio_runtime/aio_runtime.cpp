#include <aio_lang/aio_types/aio_types.h>
#include <aio_runtime/aio_runtime.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

static array_list<str_hook> *new_aio_root_type_list()
{
    array_list<str_hook> *root_type_list = new array_list<str_hook>();
    root_type_list->add(new str_hook(INTEGER));
    root_type_list->add(new str_hook(DOUBLE));
    root_type_list->add(new str_hook(STRING));
    root_type_list->add(new str_hook(BOOLEAN));
    root_type_list->add(new str_hook(VOID));
    return root_type_list;
}

static

aio_runtime::aio_runtime(const aio_runtime_type type)
{
    this->runtime_type = type;
    this->file_list = new array_list<aio_file>();
    this->types = new_aio_root_type_list();
    if (type == AIO_RUNTIME_TYPE_BUILD) {
        this->types->add(new str_hook(AIOMAIN_TYPE));
        this->types->add(new str_hook(AIOPROCESSOR_TYPE));
    }
}

aio_runtime::~aio_runtime()
{
    this->file_list->free_elements();
    this->types->free_elements();
    delete this->file_list;
    delete this->types;
}

array_list<str_hook> *aio_runtime::get_types() const
{
    return this->types;
}

array_list<aio_file> *aio_runtime::get_file_list() const
{
    return this->file_list;
}

const aio_runtime_type aio_runtime::get_runtime_type() const
{
    return this->runtime_type;
}