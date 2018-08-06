#include <mem.h>
#include "../../../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../../headers/lib/point_watcher/point_watcher.h"
#include "../../../../../../headers/lib/utils/char_utils/char_utils.h"

aio_instruction_holder *dig_instructions(const_string source_code, int *pointer_reference) {
//    aio_instruction_holder instruction_holder;
//    const size_t source_code_length = strlen(source_code);
//    point_watcher *watcher = new_point_watcher();
//    //Find function bounds:
//    for (int i = *pointer_reference; i < source_code_length; ++i) {
//        const char symbol = source_code[i];
//        const_boolean is_open_brace_condition = is_open_brace(symbol);
//        if (is_open_brace_condition && watcher->mode == POINT_UNDEFINED) {
//            watcher->start_index = i + 1;
//            watcher->mode = POINT_WATCHING_MODE;
//            watcher->counter++;
//        }
//        if (is_open_brace_condition && watcher->mode == POINT_WATCHING_MODE) {
//            watcher->counter++;
//        }
//        if (is_close_brace(symbol) && ) {
//
//        }
//
//
//
//
//
//
//
//
//
//
//
//        //독서를 시작하다 (Begin reading):
//        if (is_open_parenthesis(symbol) && watcher->mode == POINT_UNDEFINED) {
//            watcher->start_index = i + 1;
//            watcher->mode = POINT_WATCHING_MODE;
//        }
//        //독서 중지 (Stop reading):
//        if (is_close_parenthesis(symbol)) {
//            watcher->end_index = i;
//            //괄호로 호 (After parenthesis):
//            *pointer_reference = i + 1;
//            break;
//        }
//    }
//

    return NULL;
}