#include "../../../headers/lib/utils/file_utils/file_reader.h"
#include "../../../headers/lang/aio_method/aio_method.h"

void collect_method_definitions_in_manager(aio_context *context);

const_string extract_name_from_path(const_string path);

//Path example:
//"../aio_programs/test.aio", "r"
aio_context *new_aio_context(const_string path) {
    aio_context *context = calloc(1, sizeof(aio_context));
    context->method_manager = new_aio_method_manager();
    //Set name from path:
    context->name = extract_name_from_path(path);
    //Loading clean source code:
    context->source_code = read_file_and_join_to_string_without_comments(path);
    collect_method_definitions_in_manager(context);
    return context;
}

aio_method_manager *new_aio_method_manager() {
    aio_method_manager *method_manager = calloc(1, sizeof(aio_method_manager));
    method_manager->method_definition_map = new_aio_method_definition_map();
    return method_manager;
}

void invoke_method_in_manager(aio_context *context, const_string method_name, aio_bundle *bundle) {
    aio_method_definition_map *definition_map = context->method_manager->method_definition_map;
    aio_method_definition *definition = get_aio_method_definition_in_map_by_name(definition_map, method_name);
    invoke_new_aio_method(context, definition, bundle);
}