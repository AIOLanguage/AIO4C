#include <ctype.h>
#include <mem.h>
#include <stdio.h>
#include "../../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../../headers/lib/point_watcher/point_watcher.h"
#include "../../../../../../headers/lib/collections/lists/string_list.h"
#include "../../../../../../headers/lang/aio_core/aio_core.h"
#include "../../../../../../headers/lib/utils/char_utils/char_utils.h"

#define AIO_OUTPUT_RIPPER_DEBUG

enum aio_output_mode {
    OUTPUT_UNDEFINED, SINGLE_OUTPUT_MODE, MULTI_OUTPUT_MODE
};

string_list *dig_output_types(const_string source_code, int *pointer_reference) {
    string_list *output_type_list = new_string_list();
    const size_t source_code_length = strlen(source_code);
    enum aio_output_mode mode = OUTPUT_UNDEFINED;
    point_watcher *watcher = new_point_watcher();
    for (int i = *pointer_reference; i < source_code_length; ++i) {
        const char symbol = source_code[i];
        //틈새 또는 줄 바꿈 (Space or line break):
        const_boolean is_space_or_line_break_condition = is_space_or_line_break(symbol);
        //기호로 시작하다 (Starts with symbol):
        if (isalpha(symbol) && mode == OUTPUT_UNDEFINED) {
            //하나의 출력 유형 (Single output type):
            mode = SINGLE_OUTPUT_MODE;
            watcher->start_index = i;
            watcher->mode = POINT_ACTIVE_MODE;
#ifdef AIO_OUTPUT_RIPPER_DEBUG
            printf("\nOUTPUT RIPPER: START SINGLE READING...\n");
#endif
        }
        //괄호로 시작하다 (Starts with parenthesis):
        if (is_open_parentheses(symbol) && mode == OUTPUT_UNDEFINED) {
            //많은 출력 유형들 (Many output types):
            mode = MULTI_OUTPUT_MODE;
            watcher->start_index = i + 1;
            watcher->mode = POINT_ACTIVE_MODE;
#ifdef AIO_OUTPUT_RIPPER_DEBUG
            printf("\nOUTPUT RIPPER: START MULTI READING...\n");
#endif
        }
        //하나의 또는 많은 출력 방법 독서 중지 (Stop single or multi output mode reading):
        if ((is_space_or_line_break_condition && mode == SINGLE_OUTPUT_MODE)
            || (is_close_parenthesis(symbol) && mode == MULTI_OUTPUT_MODE)) {
            watcher->end_index = i;
            if (is_space_or_line_break_condition) {
                *pointer_reference = i;
            } else {
                //괄호로 호 (After parenthesis):
                *pointer_reference = i + 1;
            }
            break;
        }
        //지켜보기 잔에 공백과 줄 바꿈 건너 뛰기 (Skip whitespace and line breaks before watching):
        if (mode == OUTPUT_UNDEFINED){
            if (!is_space_or_line_break_condition){
                throw_error("OUTPUT RIPPER: 잘못된 함수 함유량 (Invalid function content)!");
            }
        }
    }
    //유형 함유량 줄 받다 (Get type content string):
    string type_content = substring(source_code, watcher->start_index, watcher->end_index);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_point_watcher(watcher);
    //------------------------------------------------------------------------------------------------------------------
#ifdef AIO_OUTPUT_RIPPER_DEBUG
    printf("OUTPUT RIPPER: RETURN TYPE CONTENT: \n-%s-\n", type_content);
#endif
    switch (mode) {
        case SINGLE_OUTPUT_MODE:
            if (contains_aio_type_in_set(type_content)) {
                add_string_in_list(output_type_list, type_content);
                return output_type_list;
            } else {
                throw_error("OUTPUT RIPPER: AIO 핵심이 유형 지원하지 않습니다 (AIO core doesn't support type)!");
            }
            break;
        case MULTI_OUTPUT_MODE: {
            const_string_array dirty_types = split_by_comma(type_content);
            const int type_number = strings_size(dirty_types);
            const_string_array clean_types = trim_all(dirty_types, type_number);
            for (int i = 0; i < type_number; ++i) {
                string type = clean_types[i];
                if (contains_aio_type_in_set(type)) {
                    add_string_in_list(output_type_list, type);
                } else {
                    throw_error("OUTPUT RIPPER: AIO 핵심이 유형 지원하지 않습니다 (AIO core doesn't support type)!");
                }
            }
            //----------------------------------------------------------------------------------------------------------
            //찌꺼기 수집기 (Garbage collector):
            free(type_content);
            free_strings(&dirty_types);
            return output_type_list;
        }
        case OUTPUT_UNDEFINED:
            throw_error("OUTPUT RIPPER: 출력 유형들을 찿을 수 없습니다! (Output types not found!)");
    }
}