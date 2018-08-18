#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"
#include "../../../../headers/lib/utils/char_utils/char_utils.h"

#define TYPE_VS_NAME 2

#define MUTABLE_VS_TYPE_VS_NAME 3

#define AIO_ARG_RIPPER_TAG "AIO_ARG_RIPPER"

#define AIO_ARG_RIPPER_DEBUG

#ifdef AIO_ARG_RIPPER_DEBUG

#include "../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

aio_variable_definition_map *dig_arguments(const_string source_code, int *pointer_reference) {
    aio_variable_definition_map *arg_definition_map = new_aio_variable_definition_map();
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
                throw_error_with_tag(AIO_ARG_RIPPER_TAG, "잘못된 함수 함유량 (Invalid function content)!");
            }
        }
    }
    //함수 인수들 함유량 줄 얻는다 (Get function arguments content string):
    const_string argument_content = substring(source_code, watcher->start, watcher->end);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_point_watcher(watcher);
    //------------------------------------------------------------------------------------------------------------------
#ifdef AIO_ARG_RIPPER_DEBUG
    log_info_string(AIO_ARG_RIPPER_TAG, "Argument content:", argument_content);
#endif
    if (!is_empty_string(argument_content)) {
        //함수 인수 함유량들 파다 (Dig arg contents):
        const_string_array dirty_arg_chunks = split_by_comma(argument_content);
        const int number_of_args = get_string_array_size(dirty_arg_chunks);
        const_string_array clean_arg_chunks = trim_all_with_line_break(dirty_arg_chunks,
                                                                       get_string_array_size(dirty_arg_chunks));
        //각 함수 인수 함유량 파다 (Dig each arg content):
        for (int j = 0; j < number_of_args; ++j) {
            const_string arg_chunk_1 = clean_arg_chunks[j];
            //Split by space:
            const_string_array dirty_arg_content_1 = split_by_space(arg_chunk_1);
            const int dirty_arg_content_size_1 = get_string_array_size(dirty_arg_content_1);
            const_string_array arg_content_1 = filter(dirty_arg_content_1, dirty_arg_content_size_1, is_empty_string);
            const int arg_content_size_1 = get_string_array_size(arg_content_1);
            //----------------------------------------------------------------------------------------------------------
            //Split by line break;
            string_list *arg_content_list = new_string_list();
            for (int k = 0; k < arg_content_size_1; ++k) {
                const_string dirty_arg_chunk_2 = arg_content_1[k];
                string_array dirty_arg_content_2 = split_by_line_break(dirty_arg_chunk_2);
                const int dirty_arg_content_size_2 = get_string_array_size(dirty_arg_content_2);
                string_array arg_content_2 = filter(dirty_arg_content_2, dirty_arg_content_size_2,
                                                    is_empty_string);
                const int arg_content_size_2 = get_string_array_size(arg_content_2);
                for (int i = 0; i < arg_content_size_2; ++i) {
                    add_string_in_list(arg_content_list, new_string(arg_content_2[i]));
                }
                //------------------------------------------------------------------------------------------------------
                //찌꺼기 수집기 (Garbage collector):
                free_strings(&dirty_arg_content_2);
                free_strings(&arg_content_2);
            }
            const int arg_content_size = arg_content_list->size;
            const_string_array clean_arg_content = trim_all_with_line_break(arg_content_list->strings,
                                                                            arg_content_size);
            string arg_type = NULL;
            string arg_name = NULL;
            boolean is_mutable = FALSE;
            aio_variable_definition *definition;
            switch (arg_content_size) {
                case TYPE_VS_NAME:
                    arg_type = new_string(clean_arg_content[0]);
                    arg_name = new_string(clean_arg_content[1]);
                    is_mutable = FALSE;
                    break;
                case MUTABLE_VS_TYPE_VS_NAME: {
                    const_string mutable_modifier_string = clean_arg_content[0];
#ifdef AIO_ARG_RIPPER_DEBUG
                    log_info_string(AIO_ARG_RIPPER_TAG, "MU", mutable_modifier_string);
#endif
                    if (is_aio_mutable_modifier(mutable_modifier_string)) {
                        arg_type = new_string(clean_arg_content[1]);
                        arg_name = new_string(clean_arg_content[2]);
                        is_mutable = TRUE;
                    } else {
                        throw_error_with_tag(AIO_ARG_RIPPER_TAG, "잘못된 'mu' 수정 자 (Invalid 'mu' modifier)!");
                    }
                }
                    break;
                default:
                    throw_error_with_tag(AIO_ARG_RIPPER_TAG, "함수 인수 함유량을 밝힐 수 없어 (Can not define arg content)!");
            }
            definition = new_aio_variable_definition(arg_name, arg_type, is_mutable);
            put_aio_variable_definition_in_map(arg_definition_map, definition);
            //----------------------------------------------------------------------------------------------------------
            //찌꺼기 수집기 (Garbage collector):
            free_strings(&dirty_arg_content_1);
            free_strings(&arg_content_1);
            free_strings_in_list(arg_content_list);
            free_string_list(arg_content_list);
            free_strings(&clean_arg_content);
        }
#ifdef AIO_ARG_RIPPER_DEBUG
        for (int k = 0; k < arg_definition_map->size; ++k) {
            const aio_variable_definition *definition = arg_definition_map->variable_definitions[k];
            printf("\n%s: -%s-, -%s-, -%d- \n", AIO_ARG_RIPPER_TAG, definition->type, definition->name,
                   definition->is_mutable_by_value);
        }
#endif
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free_strings(&dirty_arg_chunks);
        free_strings(&clean_arg_chunks);
    }
    return arg_definition_map;
}