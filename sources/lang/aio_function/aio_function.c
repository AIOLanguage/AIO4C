#include <mem.h>
#include "../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"
#include "../../../headers/lang/aio_function/aio_function_definition/aio_function_definition.h"
#include "../../../headers/lang/aio_function/aio_value/aio_value.h"
#include "../../../headers/lang/aio_function/aio_bundle/aio_bundle.h"
#include "../../../headers/lib/utils/str_hook/str_hook.h"
#include "../../../headers/lang/aio_context/aio_context.h"
#include "../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../headers/tools/aio_function_tools/aio_control_graph/aio_function_control_graph.h"

#define AIO_FUNCTION_DEBUG

#define AIO_FUNCTION_TAG "AIO_FUNCTION"

#ifdef AIO_FUNCTION_DEBUG

#include "../../../headers/lib/utils/log_utils/log_utils.h"

#endif

static aio_value_list *extract_output_values(
        const_aio_function_definition *function_definition,
        aio_bundle *bundle
)
{
    //Extract definition:
    const_str_hook_list *required_type_list = function_definition->output_type_list;
    const_str_hook_array required_type_array = required_type_list->hooks;
    const size_t required_output_size = required_type_list->size;
    //Extract bundle:
    const_aio_value_list *output_value_list = bundle->output_values;
    aio_value_array output_value_array = output_value_list->values;
    const size_t number_of_output_values = output_value_list->size;
    //Check output values:
    if (required_output_size == number_of_output_values) {
        aio_value_list *result_list = new_aio_value_list();
        for (int i = 0; i < number_of_output_values; ++i) {
            const_str_hook *required_type = required_type_array[i];
            aio_value *output_value = output_value_array[i];
            aio_value *result_value = cast_to_type(output_value, required_type);
#ifdef AIO_FUNCTION_DEBUG
            log_info_aio_value(AIO_FUNCTION_TAG, "Output value:", output_value);
            log_info_aio_value(AIO_FUNCTION_TAG, "Result value:", result_value);
#endif
            add_aio_value_in_list(result_list, result_value);
        }
        return result_list;
    } else {
        throw_error_with_tag(AIO_FUNCTION_TAG, "Number of output values doesn't match function definition!");
    }
}

aio_value_list *invoke_aio_function(
        const_aio_function_definition *definition,
        aio_bundle *bundle
)
{
    aio_function_control_graph *parent_graph = NULL;
    inflate_new_aio_root_function_control_graph(parent_graph, definition, bundle, context);
    return extract_output_values(definition, bundle);
}

aio_value_list *invoke_static_function_in_context(
        const_str_hook *function_name,
        aio_bundle *bundle
)
{
    const_aio_function_definition_list *definition_list = context->function_manager->definition_list;
    const_aio_function_definition *definition = get_aio_function_definition_in_list_by_name(
            definition_list,
            function_name
    );
#ifdef AIO_FUNCTION_DEBUG
    log_info_boolean(AIO_FUNCTION_TAG, "Definition exists:", definition != NULL);
#endif
    if (definition != NULL) {
        return invoke_aio_function(definition, bundle, context);
    } else {
        throw_error_with_hook(AIO_FUNCTION_TAG, "Function doesn't exist:", function_name);
    }
}