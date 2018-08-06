#include <stdio.h>
#include "../../../headers/lib/utils/file_utils/file_reader.h"
#include "../../../headers/lang/aio_context/aio_context.h"
#include "../../../headers/lang/aio_function/aio_function.h"

#define AIO_CONTEXT_DEBUG

void collect_function_definitions_in_manager(aio_context *context);

string extract_name_from_path(const_string path);

//경로 예 (Path example):
//"../aio_programs/test.aio"
aio_context *new_aio_context(const_string path) {
    aio_context *context = calloc(1, sizeof(aio_context));
    context->function_manager = new_aio_function_manager();
    //경로에서 이름을 넣다 (Put name from path):
    context->name = extract_name_from_path(path);
    //깨끗한 소스 코드로드 (Load clean source code):
    context->source_code = read_file_and_join_to_string_without_comments(path);
    //직능 해상력을 문맥에 모으다 (Collect function definitions in context):
    collect_function_definitions_in_manager(context);
#ifdef AIO_CONTEXT_DEBUG
    printf("\nCONTEXT: NAME\n%s\n", context->name);
    printf("\nCONTEXT: SOURCE CODE\n%s\n", context->source_code);
#endif
    return context;
}

aio_function_manager *new_aio_function_manager() {
    aio_function_manager *method_manager = calloc(1, sizeof(aio_function_manager));
    method_manager->function_definition_map = new_aio_method_definition_map();
    return method_manager;
}

void invoke_function_in_context(aio_context *context, string function_name, aio_bundle *bundle) {
    aio_function_definition_map *definition_map = context->function_manager->function_definition_map;
    aio_function_definition *definition = get_aio_method_definition_in_map_by_name(definition_map, function_name);
    invoke_new_aio_function(context, definition, bundle);
}