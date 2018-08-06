#include <mem.h>
#include <malloc.h>
#include "../../../../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../../../headers/lib/point_watcher/point_watcher.h"
#include "../../../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../../../headers/lib/utils/error_utils/error_utils.h"

const_string dig_function_body(const_string source_code, int *pointer_reference);



aio_instruction_holder *dig_instructions(const_string source_code, int *pointer_reference) {
    aio_instruction_holder instruction_holder;
    const_string function_body = dig_function_body(source_code, pointer_reference);




    return NULL;
}

const_string dig_function_body(const_string source_code, int *pointer_reference) {
    const size_t source_code_length = strlen(source_code);
    point_watcher *watcher = new_point_watcher();
    //함수 바지 멜빵 찾다 (Find function braces):
    for (int i = *pointer_reference; i < source_code_length; ++i) {
        const char symbol = source_code[i];
        const_boolean is_open_brace_condition = is_open_brace(symbol);
        //독서를 시작하다 (Begin reading):
        if (is_open_brace_condition && watcher->mode == POINT_UNDEFINED) {
            watcher->start_index = i + 1;
            watcher->mode = POINT_WATCHING_MODE;
            watcher->counter++;
        }
        if (is_open_brace_condition && watcher->mode == POINT_WATCHING_MODE) {
            watcher->counter++;
        }
        //독서 중지 (Stop reading):
        if (is_close_brace(symbol) && watcher->mode == POINT_WATCHING_MODE) {
            watcher->counter--;
            if (watcher->counter == 0) {
                watcher->end_index = i;
                *pointer_reference = i + 1;
                break;
            }
        }
        //지켜보기 잔에 공백과 줄 바꿈 건너 뙤기 (Skip whitespace and line breaks before watching):
        if (watcher->mode == POINT_UNDEFINED) {
            if (!is_space_or_line_break(symbol)) {
                throw_error("OUTPUT RIPPER: 잘못된 함수 함유량 (Invalid function content)!");
            }
        }
    }
    //Dig function body:
    const_string dirty_function_body_chunk = substring(source_code, watcher->start_index, watcher->end_index);
    const_string clean_function_body_chunk = trim_with_line_break(dirty_function_body_chunk);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_point_watcher(watcher);
    free((void *) dirty_function_body_chunk);
    return clean_function_body_chunk;
}