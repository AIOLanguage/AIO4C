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
#include "../../../headers/lang/aio_function/aio_function_definition/aio_function_definition_builder.h"


#define AIO_CONTEXT_BUILDER_TAG "AIO_CONTEXT_BUILDER_TAG"

#define AIO_CONTEXT_BUILDER_DEBUG

#ifdef AIO_CONTEXT_BUILDER_DEBUG

#include "../../../headers/lib/utils/log_utils/log_utils.h"

#endif

void upbuild_aio_context(aio_context *context) {
    const_string source_code = context->source_code;
    const size_t source_code_length = strlen(source_code);
    const_boolean is_empty_context = is_empty_string(source_code);
#ifdef AIO_CONTEXT_BUILDER_DEBUG
    log_info_boolean(AIO_CONTEXT_BUILDER_TAG, "Context is empty:", is_empty_context);
#endif
    if (is_empty_context) {
        throw_error_with_tag(AIO_CONTEXT_BUILDER_TAG, "AIO 컨텍스트가 비어있다 (AIO context is empty)!");
    }
    //함수들 찾기 준비하기 (Prepare to find functions):
    int pointer = 0;
    aio_function_definition_list *definition_list = context->function_manager->definition_list;
    while (pointer < source_code_length) {
#ifdef AIO_CONTEXT_BUILDER_DEBUG
        log_info(AIO_CONTEXT_BUILDER_TAG, "Find functions in aio context...");
#endif
        const_aio_function_definition *function_definition = build_aio_function_definition(source_code, &pointer);
        //add_aio_function_definition_in_list(definition_list, function_definition);
        break;
    }
}