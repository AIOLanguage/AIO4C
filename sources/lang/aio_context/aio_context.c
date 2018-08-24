#include <stdio.h>
#include "../../../headers/lib/utils/file_utils/file_reader.h"
#include "../../../headers/lang/aio_context/aio_context.h"
#include "../../../headers/lang/aio_function/aio_function.h"
#include "../../../headers/lib/utils/error_utils/error_utils.h"

#define AIO_CONTEXT_DEBUG

#ifdef AIO_CONTEXT_DEBUG

#define AIO_CONTEXT_TAG "AIO_CONTEXT"

#include "../../../headers/lib/utils/log_utils/log_utils.h"
#include "../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"

#endif

static const_aio_static_function_manager *new_aio_static_function_manager()
{
    aio_static_function_manager *method_manager = new_object(sizeof(aio_static_function_manager));
    method_manager->definition_list = new_aio_function_definition_list();
    return method_manager;
}

//경로 예 (Path example):
//"../aio_programs/test.aio"
const_aio_context *new_aio_context(const_string path)
{
    aio_context *context = new_object(sizeof(aio_context));
    context->function_manager = new_aio_static_function_manager();
    //경로에서 이름을 넣다 (Put name from path):
    context->name = extract_name_from_path(path);
#ifdef AIO_CONTEXT_DEBUG
    log_info_str_hook(AIO_CONTEXT_TAG, "Context name:", context->name);
#endif
    //깨끗한 소스 코드로드 (Load clean source code):
    context->source_code = read_file_and_join_to_string_without_comments(path);
#ifdef AIO_CONTEXT_DEBUG
    log_info_string(AIO_CONTEXT_TAG, "Source code:", context->source_code);
#endif
    //직능 해상력을 문맥에 모으다 (Collect function definitions in context_ref):
    upbuild_aio_context(context);
    return context;
}

/**
 * List.
 */

aio_context_list *new_aio_context_list()
{
    aio_context_list *map = new_object(sizeof(aio_context_list));
    map->capacity = 2;
    map->size = 0;
    map->contexts = new_object_array(2, sizeof(aio_context *));
    return map;
}

void update_memory_in_aio_context_list(aio_context_list *map)
{
    if (map->size + 1 == map->capacity) {
        map->capacity = map->capacity * 2;
        map->contexts = realloc(map->contexts, map->capacity * sizeof(aio_context *));
    }
}

void add_aio_context_in_list(aio_context_list *list, const_aio_context *context)
{
    const_str_hook *context_name = context->name;
    for (int i = 0; i < list->size; ++i) {
        const_str_hook *current_name = list->contexts[i]->name;
        const_boolean are_equal_strings = are_equal_hooked_str(current_name, context_name);
        if (are_equal_strings) {
            throw_error_with_tag(AIO_CONTEXT_TAG, "This context_ref name already exists!");
        }
    }
    update_memory_in_aio_context_list(list);
    list->contexts[list->size] = context;
    list->size++;
}

const_aio_context *get_aio_context_in_list_by_name(const_aio_context_list *list, const_str_hook *context_name)
{
    const int list_size = list->size;
    for (int i = 0; i < list_size; ++i) {
        const_str_hook *current_name = list->contexts[i]->name;
        const_boolean are_equal_strings = are_equal_hooked_str(current_name, context_name);
        if (are_equal_strings) {
            return list->contexts[i];
        }
    }
    return NULL;
}