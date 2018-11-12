//lang:
#include <aio_lang/aio_types/aio_types.h>
#include <aio_lang/aio_invokable/aio_function/aio_function.h>
//lib4aio:
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>

aio_function *create_function_for_aio_function_medium_test()
{
    aio_function *expected_function = new aio_function();

    //Create name:
    expected_function->name = new str_hook("ten");

    //Create expected args:
    expected_function->fields = new array_list<aio_field>(true);

    //Create expected tasks:
    expected_function->instructions = new array_list<aio_task>(true);

    //Put attributes:
    expected_function->output_type = new str_hook(DOUBLE);
    expected_function->visibility = aio_visible::AIO_VISIBILITY_PROTECTED;
    expected_function->is_array_output = true;

    //Ready:
    return expected_function;
}