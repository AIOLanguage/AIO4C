#include <aio_core/aio_core.h>

void aio_core::inflate_aio_core(const int argc, char **argv)
{

}

aio_core *aio_core::get_instance()
{
    if (!core) {
        core = new aio_core();
    }
    return core;
}

aio_core::aio_core()
{
    this->file_list = new array_list<aio_file>();
    this->types = new array_list<str_hook>();
}

aio_core::~aio_core()
{
    this->file_list->free_elements();
    this->types->free_elements();
    delete this->file_list;
    delete this->types;
}

const array_list<str_hook> *aio_core::get_types() const
{
    return this->types;
}

const array_list<aio_file> *aio_core::get_file_list() const
{
    return this->file_list;
}