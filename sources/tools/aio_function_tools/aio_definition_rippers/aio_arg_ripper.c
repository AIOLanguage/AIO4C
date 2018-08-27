#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"
#include "../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../headers/lib/utils/point_watcher/point_watcher.h"
#include "../../../../headers/lang/aio_function/aio_variable/aio_definition/aio_variable_definition.h"
#include "../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"

#define TYPE_VS_NAME 2

#define MUTABLE_VS_TYPE_VS_NAME 3

#define AIO_ARG_RIPPER_TAG "AIO_ARG_RIPPER"

#define AIO_ARG_RIPPER_DEBUG

#ifdef AIO_ARG_RIPPER_DEBUG

#include "../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

aio_variable_definition_list *dig_arguments(const_string source_code, int *pointer_reference)
{
    aio_variable_definition_list *arg_definition_map = new_aio_variable_definition_list();
    const size_t source_code_length = strlen(source_code);
    point_watcher *watcher = new_point_watcher();
    for (int i = *pointer_reference; i < source_code_length; ++i) {
        const char symbol = source_code[i];
        //독서를 시작하다 (Begin reading):
        if (is_opening_parenthesis(symbol) && watcher->mode == POINT_WATCHER_PASSIVE_MODE) {
            watcher->start = i + 1;
            watcher->mode = POINT_WATCHER_ACTIVE_MODE;
        }
        //독서 중지 (Stop reading):
        if (is_closing_parenthesis(symbol)) {
            watcher->end = i;
            //괄호로 호 (After parenthesis):
            *pointer_reference = i + 1;
            break;
        }
        //지켜보기 잔에 공백과 줄 바꿈 건너 뙤기 (Skip whitespace and line breaks before watching):
        if (watcher->mode == POINT_WATCHER_PASSIVE_MODE) {
            if (!is_space_or_line_break(symbol)) {
                throw_error_with_tag(AIO_ARG_RIPPER_TAG, "Invalid function content!");
            }
        }
    }
    //함수 인수들 함유량 줄 얻는다 (Get function arguments content string):
    const_str_hook *argument_content_chunk = new_str_hook_by_point_watcher(source_code, watcher);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_point_watcher(watcher);
    //------------------------------------------------------------------------------------------------------------------
#ifdef AIO_ARG_RIPPER_DEBUG
    log_info_str_hook(AIO_ARG_RIPPER_TAG, "Argument content:", argument_content_chunk);
#endif
    if (!is_empty_hooked_str(argument_content_chunk)) {
        //함수 인수 함유량들 파다 (Dig arg contents):
        const_str_hook_list *dirty_arg_chunks = split_str_hook_by_comma(argument_content_chunk);
#ifdef AIO_ARG_RIPPER_DEBUG
        log_info_str_hook_list(AIO_ARG_RIPPER_TAG, "Dirty Arg chunks ----->", dirty_arg_chunks);
#endif
        const_str_hook_list *clean_arg_chunks = trim_str_hook_list_with_line_break(dirty_arg_chunks);
        //각 함수 인수 함유량 파다 (Dig each arg content):
        const_str_hook_array clean_arg_chunk_array = clean_arg_chunks->hooks;
        for (int j = 0; j < clean_arg_chunks->size; ++j) {
            const_str_hook *arg_chunk = clean_arg_chunk_array[j];
            //Split by space or line break:
            const_str_hook_list *dirty_arg_content_list = split_str_hook_by_whitespace(arg_chunk);
            const_str_hook_list *clean_arg_content_list = filter_str_hook_list(
                    dirty_arg_content_list,
                    is_not_empty_hooked_str
            );
            const_str_hook_array hooks = clean_arg_content_list->hooks;
            const size_t clean_arg_content_list_size = clean_arg_content_list->size;
            str_hook *arg_type = NULL;
            const_str_hook *arg_name = NULL;
            boolean is_mutable = FALSE;
#ifdef AIO_ARG_RIPPER_DEBUG
            log_info_str_hook_list(AIO_ARG_RIPPER_TAG, "CLEAN CONTENT ----->", clean_arg_content_list);
            log_info_int(AIO_ARG_RIPPER_TAG, "Clean arg content list size:", clean_arg_content_list_size);
#endif
            if (clean_arg_content_list_size == TYPE_VS_NAME) {
                arg_type = new_str_hook_by_other(hooks[0]);
                arg_name = new_str_hook_by_other(hooks[1]);
            } else if (clean_arg_content_list_size == MUTABLE_VS_TYPE_VS_NAME) {
                const_str_hook *mutable_modifier = hooks[0];
                if (is_aio_mutable_modifier(mutable_modifier)) {
                    arg_type = new_str_hook_by_other(hooks[1]);
                    arg_name = new_str_hook_by_other(hooks[2]);
                    is_mutable = TRUE;
                } else {
                    throw_error_with_tag(AIO_ARG_RIPPER_TAG, "Invalid 'mu' modifier!");
                }
            } else {
                throw_error_with_tag(AIO_ARG_RIPPER_TAG, "Can not define arg content!");
            }
            aio_variable_definition *definition = new_aio_variable_definition(arg_name, arg_type, is_mutable);
            add_aio_variable_definition_in_list(arg_definition_map, definition);
            //----------------------------------------------------------------------------------------------------------
            //찌꺼기 수집기 (Garbage collector):
            free_str_hooks_in_list(dirty_arg_content_list);
            free_str_hook_list(dirty_arg_content_list);
            free_str_hooks_in_list(clean_arg_content_list);
            free_str_hook_list(clean_arg_content_list);
        }
#ifdef AIO_ARG_RIPPER_DEBUG
        for (int k = 0; k < arg_definition_map->size; ++k) {
            const aio_variable_definition *definition = arg_definition_map->definitions[k];
            const_string type = substring_by_str_hook(definition->type);
            const_string name = substring_by_str_hook(definition->name);
            printf("\n%s: -%s-, -%s-, -%d- \n", AIO_ARG_RIPPER_TAG, type, name, definition->is_mutable);
            free((void *) type);
            free((void *) name);
        }
#endif
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free_str_hooks_in_list(dirty_arg_chunks);
        free_str_hook_list(dirty_arg_chunks);
        free_str_hooks_in_list(clean_arg_chunks);
        free_str_hook_list(clean_arg_chunks);
    }
    return arg_definition_map;
}