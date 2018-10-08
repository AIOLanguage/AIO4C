#include <aio_runtime/aio_bundle/aio_bundle.h>
#include <lib4aio_cpp_headers/utils/struct_list/struct_list.h>

using namespace lib4aio;

struct_list *invoke_function(aio_bundle *bundle)
{

}

void invoke_main_function(aio_bundle *bundle)
{
    struct_list* result = invoke_function(bundle);
    delete result;
}