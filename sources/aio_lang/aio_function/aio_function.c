#include <mem.h>
#include <aio_tools/aio_common_tools/aio_utils/aio_value/aio_value.h>
#include <aio_tools/aio_common_tools/aio_utils/aio_bundle/aio_bundle.h>
#include <aio_lang/aio_function/aio_function_definition/aio_function_definition.h>
#include <lib/utils/type_utils/type.utils.h>
#include <lib/utils/str_hook/str_hook.h>
#include <lib/utils/error_utils/error_utils.h>
#include <aio_tools/aio_function_tools/aio_control_graph/aio_function_control_graph.h>
#include <lib/utils/str_hook/str_hook_utils/str_hook_utils.h>
#include <aio_core/aio_core.h>

#define AIO_FUNCTION_DEBUG

#define AIO_FUNCTION_TAG "AIO_FUNCTION"

#ifdef AIO_FUNCTION_DEBUG


#endif

aio_core *core;

static aio_value_list *extract_output_values(
        aio_function_definition *function_definition,
        aio_bundle *bundle
)
{
    //Extract definition:
    val required_type_list = function_definition->output_type_list;
    val required_type_array = required_type_list->hooks;
    val required_output_size = required_type_list->size;
    //Extract bundle:
    val output_value_list = bundle->output_values;
    val number_of_output_values = output_value_list->size;
    val output_value_array = output_value_list->values;
    //Check output values:
    if (required_output_size == number_of_output_values) {
        var result_list = new_aio_value_list();
        for (int i = 0; i < number_of_output_values; ++i) {
            val required_type = required_type_array[i];
            var output_value = output_value_array[i];
            var result_value = cast_to_type(output_value, required_type);
            add_aio_value_in_list(result_list, result_value);
        }
        return result_list;
    } else {
        throw_error_with_tag(AIO_FUNCTION_TAG, "Number of output values doesn't match function definition!");
    }
}

aio_value_list *invoke_aio_function(
        aio_function_definition *definition,
        aio_bundle *bundle
)
{
    aio_function_control_graph *parent_graph = NULL;
    inflate_new_aio_root_function_control_graph(parent_graph, definition, bundle);
    return extract_output_values(definition, bundle);
}

aio_value_list *invoke_static_function_in_context(
        str_hook *function_name,
        aio_bundle *bundle
)
{
    aio_function_definition_list *definition_list = core->global_function_definition_list;
    aio_function_definition *definition = get_aio_function_definition_in_list_by_name(
            definition_list,
            function_name
    );
    if (definition) {
        return invoke_aio_function(definition, bundle);
    } else {
        throw_error_with_hook(AIO_FUNCTION_TAG, "Function doesn't exist:", function_name);
    }
}