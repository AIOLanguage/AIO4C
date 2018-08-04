#include <mem.h>
#include <malloc.h>
#include <stdio.h>
#include <process.h>
#include <ctype.h>
#include <stdbool.h>
#include "../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../headers/lang/aio_core/aio_core.h"
#include "../../../headers/lang/aio_types/aio_type.h"
#include "../../../headers/lib/collections/maps/aio_variable_map.h"

aio_function_definition *delve_method_definition(const_string source_code, int *pointer_reference);

void collect_function_definitions_in_manager(aio_context *context) {
    const_string source_code = context->source_code;
    const size_t source_code_length = strlen(source_code);
    aio_function_definition_map *definition_map = context->function_manager->function_definition_map;
    if (is_empty_string(source_code)) {
        throw_error("aio context is empty!");
    }
    int pointer = 0;
    while (pointer < source_code_length) {
        aio_function_definition *method_definition = delve_method_definition(source_code, &pointer);
        //put_aio_method_definition_in_map(definition_map, method_definition);
    }
}