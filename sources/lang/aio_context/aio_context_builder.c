#include <mem.h>
#include <malloc.h>
#include <stdio.h>
#include <process.h>
#include <ctype.h>
#include <stdbool.h>
#include "../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../headers/lang/aio_core/aio_core.h"
#include "../../../headers/lang/aio_function/aio_function_definition/aio_function_definition_builder.h"


#define AIO_CONTEXT_BUILDER_TAG "AIO_CONTEXT_BUILDER_TAG"

#define AIO_CONTEXT_BUILDER_DEBUG

#ifdef AIO_CONTEXT_BUILDER_DEBUG

#include "../../../headers/lib/utils/log_utils/log_utils.h"
#include "../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"

#endif

void upbuild_aio_context(aio_context *context) {
    const_string source_code = context->source_code;
    const size_t source_code_length = strlen(source_code);
    const_boolean is_empty_context = is_empty_string(source_code);
    if (is_empty_context) {
        throw_error_with_tag(AIO_CONTEXT_BUILDER_TAG, "AIO context_ref is empty!");
    }
    //함수들 찾기 준비하기 (Prepare to find functions):
    int pointer = 0;
    aio_function_definition_list *definition_list = context->function_manager->definition_list;
    while (pointer < source_code_length) {
#ifdef AIO_CONTEXT_BUILDER_DEBUG
        log_info(AIO_CONTEXT_BUILDER_TAG, "Find functions in AIO context_ref...");
#endif
        const_aio_function_definition *function_definition = conjure_aio_function_definition(source_code, &pointer);
#ifdef AIO_CONTEXT_BUILDER_TAG
        log_info(AIO_CONTEXT_BUILDER_TAG, "Founded aio function definition:");
        log_info_str_hook(AIO_CONTEXT_BUILDER_TAG, "Name:", function_definition->name);
        log_info_str_hook_list(AIO_CONTEXT_BUILDER_TAG, "Returns:", function_definition->output_type_list);
        log_info_int(AIO_CONTEXT_BUILDER_TAG, "Number of arguments:", function_definition->number_of_args);
        const_aio_annotation_list *annotation_list = function_definition->annotation_list;
        for (int i = 0; i < annotation_list->size; ++i) {
            log_info_str_hook(AIO_CONTEXT_BUILDER_TAG, "Annotation:", annotation_list->annotations[i]->name);
        };
#endif
        add_aio_function_definition_in_list(definition_list, function_definition);
    }
}