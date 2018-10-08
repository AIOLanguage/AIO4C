#include <aio_runtime/aio_value/aio_value.h>
#include <aio_runtime/aio_bundle/aio_bundle.h>
#include <lib4aio_cpp_headers/utils/struct_list/struct_list.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

using namespace lib4aio;

aio_bundle::aio_bundle(aio_core *core_ptr, str_hook *file_path, str_hook *function_name, struct_list *input_values)
{
    this->core_ptr = core_ptr;
    this->file_path = file_path;
    this->function_name = function_name;
    this->input_values = input_values;
    this->output_values = new_struct_list(sizeof(aio_value *));

}

aio_bundle::~aio_bundle()
{
    delete this->file_path;
    delete this->function_name;
    free_struct_list(this->input_values);
    free_struct_list(this->output_values);
}
