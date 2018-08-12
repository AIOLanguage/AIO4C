#include <stdio.h>
#include "../../../headers/lib/utils/file_utils/file_reader.h"
#include "../../../headers/lang/aio_context/aio_context.h"
#include "../../../headers/lang/aio_function/aio_function.h"
#include "../../../headers/lib/utils/memory_utils/memory_utils.h"

#define AIO_CONTEXT_DEBUG

#ifdef AIO_CONTEXT_DEBUG

#define AIO_CONTEXT_TAG "AIO_CONTEXT"

#include "../../../headers/lib/utils/log_utils/log_utils.h"

#endif

void collect_function_definitions_in_manager(aio_context *context);

string extract_name_from_path(const_string path);

//경로 예 (Path example):
//"../aio_programs/test.aio"
aio_context *new_aio_context(const_string path) {
    aio_context *context = new_object(sizeof(aio_context));
    context->function_manager = new_aio_function_manager();
    //경로에서 이름을 넣다 (Put name from path):
    context->name = extract_name_from_path(path);
#ifdef AIO_CONTEXT_DEBUG
    log_info_string(AIO_CONTEXT_TAG, "NAME:", context->name);
#endif
    //깨끗한 소스 코드로드 (Load clean source code):
    context->source_code = read_file_and_join_to_string_without_comments(path);
#ifdef AIO_CONTEXT_DEBUG
    log_info_string(AIO_CONTEXT_TAG, "SOURCE CODE:\n", context->source_code);
#endif
    //직능 해상력을 문맥에 모으다 (Collect function definitions in context):
    collect_function_definitions_in_manager(context);
    return context;
}

aio_function_manager *new_aio_function_manager() {
    aio_function_manager *method_manager = new_object(sizeof(aio_function_manager));
    method_manager->function_definition_map = new_aio_method_definition_map();
    return method_manager;
}

void invoke_function_in_context(aio_context *context, string function_name, aio_bundle *bundle) {
    aio_function_definition_map *definition_map = context->function_manager->function_definition_map;
    aio_function_definition *definition = get_aio_method_definition_in_map_by_name(definition_map, function_name);
    invoke_new_aio_function(context, definition, bundle);
}