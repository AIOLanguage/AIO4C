#include <mem.h>
#include <ctype.h>
#include <stdio.h>
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../headers/lib/utils/str_hook/str_hook.h"
#include "../../../../headers/lib/utils/point_watcher/point_watcher.h"

#define AIO_FUNCTION_NAME_RIPPER_DEBUG

#ifdef AIO_FUNCTION_NAME_RIPPER_DEBUG

#include "../../../../headers/lib/utils/log_utils/log_utils.h"
#include "../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"

#endif

#define AIO_FUNCTION_NAME_RIPPER_TAG "AIO_FUNCTION_NAME_RIPPER"

const_str_hook *dig_function_name(const_string source_code, int *pointer_reference) {
    const size_t source_code_length = strlen(source_code);
    point_watcher *watcher = new_point_watcher();
    for (int i = *pointer_reference; i < source_code_length; ++i) {
        const char symbol = source_code[i];
        //틈새 또는 줄 바꿈 (Space or line break):
        const_boolean is_space_or_line_break = is_space(symbol) || is_line_break(symbol);
        const_boolean is_space_or_line_break_or_open_parenthesis = is_space_or_line_break
                                                                   || is_opening_parenthesis(symbol);
        //기호로 시작하다 (Starts with symbol):
        if (isalpha(symbol) && watcher->mode == POINT_PASSIVE_MODE) {
            watcher->start = i;
            watcher->mode = POINT_ACTIVE_MODE;
#ifdef AIO_FUNCTION_NAME_RIPPER_DEBUG
            log_info(AIO_FUNCTION_NAME_RIPPER_TAG, "Start reading...");
#endif
        }
        //독서 중지 (Stop reading):
        if (is_space_or_line_break_or_open_parenthesis && watcher->mode == POINT_ACTIVE_MODE) {
            watcher->end = i;
            *pointer_reference = i;
            break;
        }
        //지켜보기 잔에 공백과 줄 바꿈 건너 뛰기 (Skip whitespace and line breaks before watching):
        if (watcher->mode == POINT_PASSIVE_MODE) {
            if (!is_space_or_line_break) {
                throw_error_with_tag(AIO_FUNCTION_NAME_RIPPER_TAG, "잘못된 함수 함유량 (Invalid function content)!");
            }
        }
    }
    //함수 이름 줄 받다 (Get function name string):
    const_str_hook *function_name = new_str_hook_by_point_watcher(source_code, watcher);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_point_watcher(watcher);
    //------------------------------------------------------------------------------------------------------------------
#ifdef AIO_FUNCTION_NAME_RIPPER_DEBUG
    log_info_str_hook(AIO_FUNCTION_NAME_RIPPER_TAG, "Function name:", function_name);
#endif
    return function_name;
}