#include <mem.h>
#include <stdio.h>
#include <process.h>
#include <malloc.h>
#include "../../../headers/lib/collections/lists/string_list.h"
#include "../../../headers/lang/aio_function/aio_bundle/aio_bundle.h"
#include "../../../headers/lang/aio_context/aio_context.h"
#include "../../../headers/lang/aio_function/aio_function.h"

void invoke_new_aio_function(aio_context *aio_context, aio_function_definition *function_definition,
                             aio_bundle *bundle) {
    aio_variable_map *arg_map = new_aio_variable_map();
    aio_variable_definition_map *arg_definition_map = function_definition->arg_definition_map;
    for (int i = 0; i < arg_definition_map->size; ++i) {
        const_string string_value = bundle->input_values->strings[i];
        aio_value* value = new_aio_value(string_value);
        aio_variable* arg = new_aio_variable_by_definition(arg_definition_map->variable_definitions[i], value);
        put_aio_variable_in_map(arg_map, arg);
    }
    //Create the same aio function:
    aio_function *function = calloc(1, sizeof(aio_function));
    //Create function container:
    function->variable_map = arg_map;
    //Reproduce function:
    reproduce_method(aio_context, function_definition, function, bundle);
}