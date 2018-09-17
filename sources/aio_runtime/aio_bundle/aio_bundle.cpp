#include <aio_runtime/aio_value/aio_value.h>
#include <aio_runtime/aio_bundle/aio_bundle.h>
#include <lib4aio_cpp_headers/utils/struct_list/struct_list.h>

using namespace lib4aio;

aio_bundle::aio_bundle(str_hook *function_name, struct_list *input_values)
{
    this->function_name = function_name;
    this->input_values = input_values;
    this->output_values = new_struct_list(sizeof(aio_value *));
}

const struct lib4aio::str_hook *aio_bundle::get_function_name() const
{
    return this->function_name;
}

aio_bundle::~aio_bundle()
{
    delete this->function_name;
    free_struct_list(this->input_values);
    free_struct_list(this->output_values);
}

const struct_list *aio_bundle::get_input_values() const
{
    return this->input_values;
}

const struct_list *aio_bundle::get_output_values() const
{
    return this->output_values;
}
