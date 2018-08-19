#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"
#include "../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../headers/lib/utils/point_watcher/point_watcher.h"
#include "../../../../headers/lang/aio_function/aio_variable/aio_definition/aio_variable_definition.h"
#include "../../../../headers/lib/utils/str_hook/str_hook.h"
#include "../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"

#define TYPE_VS_NAME 2

#define MUTABLE_VS_TYPE_VS_NAME 3

#define AIO_ARG_RIPPER_TAG "AIO_ARG_RIPPER"

#define AIO_ARG_RIPPER_DEBUG

#ifdef AIO_ARG_RIPPER_DEBUG

#include "../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

aio_variable_definition_list *dig_arguments(const_string source_code, int *pointer_reference) {
    aio_variable_definition_list *arg_definition_map = new_aio_variable_definition_list();
    const size_t source_code_length = strlen(source_code);
    point_watcher *watcher = new_point_watcher();
    for (int i = *pointer_reference; i < source_code_length; ++i) {
        const char symbol = source_code[i];
        //독서를 시작하다 (Begin reading):
        if (is_opening_parenthesis(symbol) && watcher->mode == POINT_PASSIVE_MODE) {
            watcher->start = i + 1;
            watcher->mode = POINT_ACTIVE_MODE;
        }
        //독서 중지 (Stop reading):
        if (is_closing_parenthesis(symbol)) {
            watcher->end = i;
            //괄호로 호 (After parenthesis):
            *pointer_reference = i + 1;
            break;
        }
        //지켜보기 잔에 공백과 줄 바꿈 건너 뙤기 (Skip whitespace and line breaks before watching):
        if (watcher->mode == POINT_PASSIVE_MODE) {
            if (!is_space_or_line_break(symbol)) {
                throw_error_with_tag(AIO_ARG_RIPPER_TAG, "Invalid function content!");
            }
        }
    }
    //함수 인수들 함유량 줄 얻는다 (Get function arguments content string):
    const_str_hook *argument_content = new_str_hook_by_point_watcher(source_code, watcher);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_point_watcher(watcher);
    //------------------------------------------------------------------------------------------------------------------
#ifdef AIO_ARG_RIPPER_DEBUG
    log_info_string_hook(AIO_ARG_RIPPER_TAG, "Argument content:", argument_content);
#endif
    if (!is_empty_hooked_str(argument_content)) {
        //함수 인수 함유량들 파다 (Dig arg contents):
        const_str_hook_list *dirty_arg_chunks = split_str_hook_by_comma(argument_content);
        const_str_hook_list *clean_arg_chunks = trim_str_hook_list_with_line_break(dirty_arg_chunks);
        //각 함수 인수 함유량 파다 (Dig each arg content):
        for (int j = 0; j < clean_arg_chunks->size; ++j) {
            const_str_hook *arg_chunk_1 = clean_arg_chunks->hooks[j];
            //Split by space:
            const_str_hook_list *dirty_arg_content_1 = split_str_hook_by_space(arg_chunk_1);
            const_str_hook_list *arg_content_1 = filter_str_hook_list(dirty_arg_content_1, is_empty_hooked_str);
            //----------------------------------------------------------------------------------------------------------
            //Split by line break;
            str_hook_list *arg_content_list = new_str_hook_list();
            for (int k = 0; k < arg_content_1->size; ++k) {
                const_str_hook *dirty_arg_chunk_2 = arg_content_1->hooks[k];
                const_str_hook_list *dirty_arg_content_2 = split_str_hook_by_line_break(dirty_arg_chunk_2);
                const_str_hook_list *arg_content_2 = filter_str_hook_list(dirty_arg_content_2, is_empty_hooked_str);
                for (int i = 0; i < arg_content_2->size; ++i) {
                    add_str_hook_in_list(arg_content_list, new_str_hook_by_other(arg_content_2->hooks[i]));
                }
                //------------------------------------------------------------------------------------------------------
                //찌꺼기 수집기 (Garbage collector):
                free_str_hooks_in_list(dirty_arg_content_2);
                free_str_hooks_in_list(arg_content_2);
                free_str_hook_list(arg_content_2);
                free_str_hook_list(dirty_arg_content_2);
            }
            const_str_hook_list *clean_arg_content = trim_str_hook_list_with_line_break(arg_content_list);
            const_str_hook_array hooks = clean_arg_content->hooks;
            str_hook *arg_type = NULL;
            const_str_hook *arg_name = NULL;
            boolean is_mutable = FALSE;
            switch (arg_content_list->size) {
                case TYPE_VS_NAME:
                    arg_type = new_str_hook_by_other(hooks[0]);
                    arg_name = new_str_hook_by_other(hooks[1]);
                    break;
                case MUTABLE_VS_TYPE_VS_NAME: {
                    const_str_hook *mutable_modifier_string = hooks[0];
#ifdef AIO_ARG_RIPPER_DEBUG
                    log_info_string_hook(AIO_ARG_RIPPER_TAG, "MU", mutable_modifier_string);
#endif
                    if (is_aio_mutable_modifier_hooked(mutable_modifier_string)) {
                        arg_type = new_str_hook_by_other(hooks[1]);
                        arg_name = new_str_hook_by_other(hooks[2]);
                        is_mutable = TRUE;
                    } else {
                        throw_error_with_tag(AIO_ARG_RIPPER_TAG, "Invalid 'mu' modifier!");
                    }
                }
                    break;
                default:
                    throw_error_with_tag(AIO_ARG_RIPPER_TAG, "Can not define arg content!");
            }
            aio_variable_definition *definition = new_aio_variable_definition(arg_name, arg_type, is_mutable);
            add_aio_variable_definition_in_list(arg_definition_map, definition);
            //----------------------------------------------------------------------------------------------------------
            //찌꺼기 수집기 (Garbage collector):
            free_str_hooks_in_list(dirty_arg_content_1);
            free_str_hook_list(dirty_arg_content_1);
            free_str_hooks_in_list(arg_content_1);
            free_str_hook_list(arg_content_1);
            free_str_hooks_in_list(arg_content_list);
            free_str_hook_list(arg_content_list);
            free_str_hooks_in_list(clean_arg_content);
            free_str_hook_list(clean_arg_content);
        }
#ifdef AIO_ARG_RIPPER_DEBUG
        for (int k = 0; k < arg_definition_map->size; ++k) {
            const aio_variable_definition *definition = arg_definition_map->definitions[k];
            const_string type = substring_by_str_hook(definition->type);
            const_string name = substring_by_str_hook(definition->name);
            printf("\n%s: -%s-, -%s-, -%d- \n", AIO_ARG_RIPPER_TAG, type, name, definition->is_mutable_by_value);
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