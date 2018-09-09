#include <stdlib.h>
#include <aio_utils/aio_value/aio_value.h>
#include <aio_utils/aio_bundle/aio_bundle.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

using namespace lib4aio;


aio_bundle::aio_bundle(
        lib4aio::str_hook *file_path,
        lib4aio::str_hook *function_name,
        struct struct_list *input_values
)
{
    this->file_path = file_path;
    this->function_name = function_name;
    this->input_values = input_values;
    this->output_values = new_struct_list(sizeof(aio_value *));
}

const struct lib4aio::str_hook *aio_bundle::get_path() const
{
    return this->file_path;
}

const struct lib4aio::str_hook *aio_bundle::get_function_name() const
{
    return this->function_name;
}

aio_bundle::~aio_bundle()
{
    delete this->file_path;
    delete this->function_name;
    free_struct_list(this->input_values);
    free_struct_list(this->output_values);
}