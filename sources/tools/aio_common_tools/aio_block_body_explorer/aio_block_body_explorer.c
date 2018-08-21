#include <malloc.h>
#include <mem.h>
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../headers/lib/utils/point_watcher/point_watcher.h"

#define AIO_BLOCK_BODY_EXPLORER_DEBUG

#define AIO_BLOCK_BODY_EXPLORER_TAG "AIO_BLOCK_BODY_EXPLORER"

#ifdef AIO_BLOCK_BODY_EXPLORER_DEBUG

#include "../../../../headers/lib/utils/log_utils/log_utils.h"

#endif


void explore_aio_context_bounds(const_string source_code, int *start_index, int *end_index,
                                boolean (*opening_bound_condition)(const char),
                                boolean (*closing_bound_condition)(const char)) {
    const size_t source_code_length = strlen(source_code);
    //Prepare to find bounds:
    point_watcher *watcher = new_point_watcher();
    boolean is_found_start_index = FALSE;
    boolean is_found_end_index = FALSE;
    //함수 바지 멜빵 찾다 (Find function braces):
    for (int i = *start_index; i < source_code_length; ++i) {
        const char symbol = source_code[i];
        //Check symbol:
        const_boolean is_open_brace_cond = opening_bound_condition(symbol);
        const_boolean is_close_brace_cond = closing_bound_condition(symbol);
        const_boolean is_not_whitespace_cond = !is_space_or_line_break(symbol);
        //Meet open brace:
        if (is_open_brace_cond) {
            //독서를 시작하다 (Begin reading):
            if (watcher->mode == POINT_WATCHER_PASSIVE_MODE) {
                watcher->start = i;
                watcher->mode = POINT_WATCHER_ACTIVE_MODE;
                is_found_start_index = TRUE;
            }
            if (watcher->mode == POINT_WATCHER_ACTIVE_MODE) {
                watcher->pointer++;
            }
        }
        if (is_close_brace_cond) {
            //Body doesn't start with close brace:
            if (watcher->mode == POINT_WATCHER_PASSIVE_MODE) {
                throw_error_with_tag(AIO_BLOCK_BODY_EXPLORER_TAG, "Invalid start bound!");
            }
            if (watcher->mode == POINT_WATCHER_ACTIVE_MODE) {
                watcher->pointer--;
                //독서 중지 (Stop reading):
                const_boolean is_last_close_brace = watcher->pointer == 0;
                if (is_last_close_brace) {
                    watcher->end = i + 1;
                    is_found_end_index = TRUE;
                    break;
                }
            }
        }
        //지켜보기 잔에 공백과 줄 바꿈 건너 뙤기 (Skip whitespace and line breaks before watching):
        if (watcher->mode == POINT_WATCHER_PASSIVE_MODE) {
            if (is_not_whitespace_cond) {
                throw_error_with_tag(AIO_BLOCK_BODY_EXPLORER_TAG, "Invalid content!");
            }
        }
    }
    if (is_found_start_index && is_found_end_index) {
        *start_index = watcher->start;
        *end_index = watcher->end;
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free_point_watcher(watcher);
    } else {
        throw_error_with_tag(AIO_BLOCK_BODY_EXPLORER_TAG, "Bounds not found!");
    }
}


void explore_aio_block_bounds(const_string source_code, int *start_index, int *end_index) {
    explore_aio_context_bounds(source_code, start_index, end_index, is_opening_brace, is_closing_brace);
}

void explore_aio_header_bounds(const_string source_code, int *start_index, int *end_index) {
    explore_aio_context_bounds(source_code, start_index, end_index, is_opening_parenthesis, is_closing_parenthesis);
}

const_boolean has_context_rest(const_string body_string, point_watcher *watcher) {
    while (watcher->pointer < watcher->end) {
        const char symbol = body_string[watcher->pointer];
        if (!is_space_or_line_break(symbol)) {
            watcher->mode = POINT_WATCHER_ACTIVE_MODE;
            return FALSE;
        } else {
            watcher->start++;
            watcher->pointer++;
        }
    }
    return TRUE;
}