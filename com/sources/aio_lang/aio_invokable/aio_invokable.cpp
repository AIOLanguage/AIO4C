//lang:
#include <aio_lang/aio_invokable/aio_invokable.h>
//#include <aio_lang/aio_schemable/aio_schemable.cpp>
//lib4aio:
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <aio_lang/aio_types/aio_types.h>

using namespace lib4aio;

aio_invokable::aio_invokable()
{

    this->output_type = nullptr;
    this->is_array_output = false;
    this->arg_count = 0;
}

aio_invokable::~aio_invokable()
{
    delete this->output_type;
}