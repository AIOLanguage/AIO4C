#include <malloc.h>
#include <mem.h>
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lib/point_watcher/point_watcher.h"
#include "../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"

#define AIO_BLOCK_BODY_EXPLORER_DEBUG

#define AIO_BLOCK_BODY_EXPLORER_TAG "AIO_BLOCK_BODY_EXPLORER"

#ifdef AIO_BLOCK_BODY_EXPLORER_DEBUG

#include "../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

void explore_block_body(const_string source_code, int *start_index, int *end_index) {
    const size_t source_code_length = strlen(source_code);
    //Prepare to find bounds:
    point_watcher *watcher = new_point_watcher();
    boolean is_found_start_index = FALSE;
    boolean is_found_end_index = FALSE;
    //함수 바지 멜빵 찾다 (Find function braces):
    for (int i = *start_index; i < source_code_length; ++i) {
        const char symbol = source_code[i];
        //Check symbol:
        const_boolean is_open_brace_cond = is_open_brace(symbol);
        const_boolean is_close_brace_cond = is_close_brace(symbol);
        const_boolean is_not_whitespace_cond = !is_space_or_line_break(symbol);
        //Meet open brace:
        if (is_open_brace_cond) {
            //독서를 시작하다 (Begin reading):
            if (watcher->mode == POINT_PASSIVE_MODE) {
                //Skip first brace:
                watcher->start_index = i;
                watcher->mode = POINT_ACTIVE_MODE;
                is_found_start_index = TRUE;
#ifdef AIO_BLOCK_BODY_EXPLORER_DEBUG
                log_info_char(AIO_BLOCK_BODY_EXPLORER_TAG, "FIND START BRACE:", symbol);
#endif
            }
            if (watcher->mode == POINT_ACTIVE_MODE) {
                watcher->pointer++;
            }
        }
        //Meet close brace:
        if (is_close_brace_cond) {
            //Body doesn't start with close brace:
            if (watcher->mode == POINT_PASSIVE_MODE) {
                throw_error_with_tag(AIO_BLOCK_BODY_EXPLORER_TAG, "Body doesn't start with close brace!");
            }
            if (watcher->mode == POINT_ACTIVE_MODE) {
                watcher->pointer--;
                //독서 중지 (Stop reading):
                const_boolean is_last_close_brace = watcher->pointer == 0;
                if (is_last_close_brace) {
                    watcher->end_index = i + 1;
                    is_found_end_index = TRUE;
#ifdef AIO_BLOCK_BODY_EXPLORER_DEBUG
                    log_info_char(AIO_BLOCK_BODY_EXPLORER_TAG, "FIND LAST BRACE:", symbol);
#endif
                    break;
                }
            }
        }
        //지켜보기 잔에 공백과 줄 바꿈 건너 뙤기 (Skip whitespace and line breaks before watching):
        if (watcher->mode == POINT_PASSIVE_MODE) {
            if (is_not_whitespace_cond) {
                throw_error_with_tag(AIO_BLOCK_BODY_EXPLORER_TAG, "Invalid function content!");
            }
        }
    }
    if (is_found_start_index && is_found_end_index) {
        *start_index = watcher->start_index;
        *end_index = watcher->end_index;
#ifdef AIO_BLOCK_BODY_EXPLORER_DEBUG
        log_info_int(AIO_BLOCK_BODY_EXPLORER_TAG, "Start index:", *start_index);
        log_info_char(AIO_BLOCK_BODY_EXPLORER_TAG, "Start index:", source_code[*start_index]);
        log_info_int(AIO_BLOCK_BODY_EXPLORER_TAG, "End index:", *end_index);
        log_info_char(AIO_BLOCK_BODY_EXPLORER_TAG, "End index:", source_code[*end_index]);
        const_string function_body = substring_by_point_watcher(source_code, watcher);
        log_info_string(AIO_BLOCK_BODY_EXPLORER_TAG, "Function body:", function_body);
        free((void *) function_body);
#endif
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free_point_watcher(watcher);
    } else {
        throw_error_with_tag(AIO_BLOCK_BODY_EXPLORER_TAG, "Invalid function body braces!");
    }
}

const_boolean is_end_of_block_body(const_string function_body_string, point_watcher *watcher) {
    while (watcher->pointer < watcher->end_index) {
        const char symbol = function_body_string[watcher->pointer];
        if (!is_space_or_line_break(symbol)) {
            watcher->mode = POINT_ACTIVE_MODE;
            return FALSE;
        } else {
            watcher->pointer++;
        }
    }
    return TRUE;
}