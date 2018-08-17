#include <malloc.h>
#include <mem.h>
#include <ctype.h>
#include "../../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../headers/lib/point_watcher/point_watcher.h"
#include "../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../headers/lib/utils/string_utils/string_builder.h"
#include "../../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"
#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/tools/aio_parsers/aio_spiders/aio_spider.h"

/**
 * 주 논리 (Business logic).
 */

#define AIO_IF_SPIDER_DEBUG

#define AIO_IF_SPIDER_TAG "AIO_IF_SPIDER"

#ifdef AIO_IF_SPIDER_DEBUG

#include "../../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

/**
 * Refresh
 */

void refresh_if_spider(aio_spider *spider, point_watcher *ripper_watcher) {
    //거미의 조건 리셋 (Reset spider state):
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    //재료 리셋 (Reset materials):
    aio_if_materials *materials = spider->get.if_materials;
    materials->main_watcher->start = ripper_watcher->pointer;
    materials->main_watcher->end = ripper_watcher->pointer;
    materials->main_watcher->mode = POINT_PASSIVE_MODE;
    reset_point_watcher(materials->header_watcher);
    reset_point_watcher(materials->true_watcher);
    reset_point_watcher(materials->false_watcher);
    materials->scope_type = AIO_IF_MODIFIER_SCOPE;
    materials->branch_type = AIO_UNDEFINED_BRANCHES;
    free(materials->condition);
}

/**
 * 거미를 비우다 (Free spider).
 */

void free_if_spider(aio_spider *spider) {
    aio_if_materials *materials = spider->get.if_materials;
    free_point_watcher(materials->main_watcher);
    free_point_watcher(materials->header_watcher);
    free_point_watcher(materials->true_watcher);
    free_point_watcher(materials->false_watcher);
    free(materials->condition);
    free(materials);
    free(spider);
}

/**
 * 건설자 (Constructor).
 */

aio_spider *new_aio_if_spider(point_watcher *ripper_watcher) {
    aio_spider *spider = new_object(sizeof(aio_spider));
    //함수들을 놓다 (Put functions):
    spider->refresh = refresh_if_spider;
    spider->is_found_instruction = is_found_if_instruction;
    spider->weave_instruction_for = weave_if_instruction_for;
    spider->free = free_if_spider;
    //재료들을 만들다 (Create materials):
    aio_if_materials *materials = new_object(sizeof(aio_if_materials));
    materials->main_watcher = new_point_watcher();
    materials->main_watcher->start = ripper_watcher->start;
    materials->main_watcher->end = ripper_watcher->pointer;
    materials->header_watcher = new_point_watcher();
    materials->true_watcher = new_point_watcher();
    materials->false_watcher = new_point_watcher();
    materials->scope_type = AIO_IF_MODIFIER_SCOPE;
    materials->branch_type = AIO_UNDEFINED_BRANCHES;
    //재료들을 놓다 (Set materials):
    spider->get.if_materials = materials;
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    return spider;
}

/**
 * 수색 (Searching).
 */

const aio_spider_message
is_found_if_instruction(const_string source_code, point_watcher *ripper_watcher, aio_spider *spider) {
    //재료들을 추출하다 (Extract materials):
    const aio_if_materials *materials = spider->get.if_materials;
    point_watcher *main_watcher = materials->main_watcher;
    main_watcher->end = ripper_watcher->pointer;
    //스캐닝 준비 (Prepare for scanning):
    const char current_symbol = source_code[main_watcher->end];
    //TODO: 코드 복제 (Code duplication)!
    if (main_watcher->mode == POINT_PASSIVE_MODE) {
        if (is_space_or_line_break(current_symbol)) {
            main_watcher->start++;
        } else {
            main_watcher->mode = POINT_ACTIVE_MODE;
        }
    }
    if (main_watcher->mode == POINT_ACTIVE_MODE) {
        if (materials->scope_type == AIO_IF_MODIFIER_SCOPE) {
            handle_if_modifier_scope(source_code, spider);
        }
        if (materials->scope_type == AIO_IF_CONDITION_SCOPE) {
            handle_condition_scope(source_code, spider);
            return spider->message;
        }
        if (materials->scope_type == AIO_IF_TRUE_BODY_SCOPE) {
            handle_true_body_scope(source_code, spider);
            return spider->message;
        }
        if (materials->scope_type == AIO_IF_FALSE_BODY_SCOPE) {
            handle_false_body_scope(source_code, spider);
        }
    }
    return spider->message;
}

void handle_if_modifier_scope(const_string source_code, aio_spider *spider) {
    aio_if_materials *materials = spider->get.if_materials;
    point_watcher *main_watcher = materials->main_watcher;
    const int current_position = main_watcher->end;
    const char current_symbol = source_code[current_position];
    //현재 기호를 확인하다 (Check current symbol):
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    const_boolean is_open_parenthesis_cond = is_opening_parenthesis(current_symbol);
    if (is_whitespace_cond || is_open_parenthesis_cond) {
        const int start_index = main_watcher->start;
        const int end_index = main_watcher->end;
        const int hold_positions = end_index - start_index;
        if (hold_positions == 2) {
            const_boolean is_if_modifier = source_code[start_index] == 'i' && source_code[start_index + 1] == 'f';
            if (is_if_modifier) {
                //주요 당직자를 바꾼다 (Shift main watcher):
                main_watcher->start = end_index;
                main_watcher->mode = POINT_PASSIVE_MODE;
                //범위를 바꾼다 (Change scope):
                materials->scope_type = AIO_IF_CONDITION_SCOPE;
                //메시지 놓다 (Set message):
                spider->message = AIO_SPIDER_FOUND_MATERIALS;
#ifdef AIO_IF_SPIDER_DEBUG
                log_info(AIO_IF_SPIDER_TAG, "Pass modifier scope!");
#endif
            }
        }
    }
}

void handle_condition_scope(const_string string_web, aio_spider *spider) {
    aio_if_materials *materials = spider->get.if_materials;
    point_watcher *main_watcher = materials->main_watcher;
    point_watcher *header_watcher = materials->header_watcher;
    //현재 위치를 정의하다 (Define current position):
    const int current_position = main_watcher->end;
    const char current_symbol = string_web[current_position];
    //조건들을 확인하다 (Check conditions):
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    const_boolean is_opening_parenthesis_cond = is_opening_parenthesis(current_symbol);
    const_boolean is_closing_parenthesis_cond = is_closing_parenthesis(current_symbol);
    //여는 괄호를 만나다 (Meet opening parenthesis):
    if (is_opening_parenthesis_cond) {
        //조건의 시작이 (Start of condition):
        if (header_watcher->mode == POINT_PASSIVE_MODE) {
            //여는 괄호를 뛰어 넘다 (Jump over open parenthesis):
            header_watcher->start = main_watcher->end + 1;
            header_watcher->mode = POINT_ACTIVE_MODE;
        }
        //조건안의 여는 괄호 (Opening parenthesis inside condition):
        if (header_watcher->mode == POINT_ACTIVE_MODE) {
            //괄호들을 계산하다 (Count parentheses):
            header_watcher->pointer++;
        }
        return;
    }
    //닫는 괄호를 만나다 (Meet closing parenthesis):
    if (is_closing_parenthesis_cond) {
        //조건의 시작이 아님 (Not the beginning of a condition):
        if (header_watcher->mode == POINT_PASSIVE_MODE) {
            throw_error_with_tag(AIO_IF_SPIDER_TAG, "Condition can not start with close parenthesis!");
        }
        //조건안의 닫는 괄호 (Closing parenthesis inside condition):
        if (header_watcher->mode == POINT_ACTIVE_MODE) {
            header_watcher->pointer--;
            //조건의 닫는 괄호 (Closing parenthesis of condition):
            if (header_watcher->pointer == 0) {
                //닫는 괄호를 보류하지 않다 (Don't hold closing parenthesis):
                header_watcher->end = current_position;
                //주요 당직자를 바꾼다 (Shift main watcher):
                main_watcher->start = main_watcher->end + 1;
                main_watcher->mode = POINT_PASSIVE_MODE;
                //범위를 바꾼다 (Change scope):
                materials->scope_type = AIO_IF_TRUE_BODY_SCOPE;
                //조건을 추출하다 (Extract condition):
                const_string dirty_condition = substring_by_point_watcher(string_web, header_watcher);
                string clean_condition = squeeze_string(dirty_condition);
#ifdef AIO_IF_SPIDER_DEBUG
                log_info_string(AIO_IF_SPIDER_TAG, "Captured condition", clean_condition);
#endif
                materials->condition = clean_condition;
                //------------------------------------------------------------------------------------------------------
                //찌꺼기 수집기 (Garbage collector):
                free((void *) dirty_condition);
            }
        }
        return;
    }
    //조건전 공백들을 건너 뛰다 (Skip whitespaces before condition):
    if (!is_whitespace_cond && header_watcher->mode == POINT_PASSIVE_MODE) {
        throw_error_with_tag(AIO_IF_SPIDER_TAG, "Invalid context after 'if' modifier!");
    }
}

void handle_true_body_scope(const_string source_code, aio_spider *spider) {
    aio_if_materials *materials = spider->get.if_materials;
    point_watcher *main_watcher = materials->main_watcher;
    point_watcher *true_watcher = materials->true_watcher;
    //현재 위치를 정의하다 (Define current position):
    const int current_position = main_watcher->end;
    const char current_symbol = source_code[current_position];
    //조건들을 확인하다 (Check conditions):
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    const_boolean is_opening_brace_cond = is_opening_brace(current_symbol);
    const_boolean is_closing_brace_cond = is_closing_brace(current_symbol);
    const_boolean is_colon_cond = is_colon(current_symbol);
    //여는 중괄호를 만나다 (Meet a opening brace):
    if (is_opening_brace_cond) {
        //'true' 블록의 시작이 (Start of 'true' body):
        if (true_watcher->mode == POINT_PASSIVE_MODE) {
            //여는 중괄호를 보류하다 (Hold a opening brace):
            true_watcher->start = current_position;
            true_watcher->mode = POINT_ACTIVE_MODE;
        }
        //블록안에 여는 중괄호 (Opening brace inside body):
        if (true_watcher->mode == POINT_ACTIVE_MODE) {
            //중괄호들을 계산하다 (Count braces):
            true_watcher->pointer++;
        }
    }
    //닫는 중괄호를 만나다 (Meet close brace):
    if (is_closing_brace_cond) {
        //블록의 시작이 아님 (Not the beginning of a condition):
        if (true_watcher->mode == POINT_PASSIVE_MODE) {
            throw_error_with_tag(AIO_IF_SPIDER_TAG, "True body can not start with close brace!");
        }
        //블록안에 닫는 중괄호 (Closing brace inside block):
        if (true_watcher->mode == POINT_ACTIVE_MODE) {
            true_watcher->pointer--;
            //블록의 닫는 중괄호 (Closing brace of block):
            if (true_watcher->pointer == 0) {
                //닫는 중괄호를 보류하다 (Hold close brace):
                true_watcher->end = main_watcher->end + 1;
                true_watcher->mode = POINT_UNDEFINED_MODE;
#ifdef AIO_IF_SPIDER_DEBUG
                const_string true_body = substring_by_point_watcher(source_code, true_watcher);
                log_info_string(AIO_IF_SPIDER_TAG, "True body:", true_body);
                free((void *) true_body);
#endif
                return;
            }
        }
    }
    //조건후에 공백들을 건너 뛰다 (Skip whitespaces after condition):
    if (!is_whitespace_cond) {
        if (true_watcher->mode == POINT_PASSIVE_MODE) {
            throw_error_with_tag(AIO_IF_SPIDER_TAG, "Invalid context after 'if' condition!");
        }
        //'false' 수정 자 또는 다른 기호 기다리다 (Waiting for 'false' modifier or other symbol):
        if (true_watcher->mode == POINT_UNDEFINED_MODE) {
            //콜론을 만나면 수정 자입니다 (If meet colon then this is 'false' modifier):
            if (is_colon_cond) {
                //분기 유형을 놓다 (Set branch type):
                materials->branch_type = AIO_HAS_TRUE_AND_FALSE_BRANCHES;
                //범위를 바꾼다 (Change scope):
                materials->scope_type = AIO_IF_FALSE_BODY_SCOPE;
#ifdef AIO_IF_SPIDER_DEBUG
                log_info(AIO_IF_SPIDER_TAG, "Prepare to find false body...!");
#endif
            } else {
                //분기 유형을 놓다 (Set branch type):
                materials->branch_type = AIO_HAS_TRUE_BRANCH;
                //범위를 바꾼다 (Change scope):
                materials->scope_type = AIO_IF_WEAVING_SCOPE;
                //메시지 놓다 (Set message):
                spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
#ifdef AIO_IF_SPIDER_DEBUG
                log_info(AIO_IF_SPIDER_TAG, "False body is absent! Prepare to weave...");
#endif
            }
            //주요 당직자를 바꾼다 (Shift main watcher):
            main_watcher->start = main_watcher->end + 1;
            main_watcher->mode = POINT_PASSIVE_MODE;
        }
    }
}

void handle_false_body_scope(const_string source_code, aio_spider *spider) {
    aio_if_materials *materials = spider->get.if_materials;
    point_watcher *main_watcher = materials->main_watcher;
    point_watcher *false_watcher = materials->false_watcher;
    //현재 위치를 정의하다 (Define current position):
    const int current_position = main_watcher->end;
    const char current_symbol = source_code[current_position];
    //현재 기호를 확인하다 (Check current symbol):
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    const_boolean is_opening_brace_cond = is_opening_brace(current_symbol);
    const_boolean is_closing_brace_cond = is_closing_brace(current_symbol);
    //여는 중괄호를 만나다 (Meet opening brace):
    if (is_opening_brace_cond) {
        //'false' 블록의 시작이 (Start of 'false body):
        if (false_watcher->mode == POINT_PASSIVE_MODE) {
            //여는 중괄호를 보류하다 (Hold opening brace):
            false_watcher->start = current_position;
            false_watcher->mode = POINT_ACTIVE_MODE;
        }
        //블록안에 여는 중괄호 (Opening brace in body):
        if (false_watcher->mode == POINT_ACTIVE_MODE) {
            //중괄호를 계산하다 (Count braces):
            false_watcher->pointer++;
        }
    }
    //닫는 중괄호를 만나다 (Meet closing brace):
    if (is_closing_brace_cond) {
        //블록의 시작이 아님  (Not a start of body):
        if (false_watcher->mode == POINT_PASSIVE_MODE) {
            throw_error_with_tag(AIO_IF_SPIDER_TAG, "False body can not start with close brace!");
        }
        //'false' 블록안에 딛는 중괄호 (Closing brace in 'false' body):
        if (false_watcher->mode == POINT_ACTIVE_MODE) {
            false_watcher->pointer--;
            if (false_watcher->pointer == 0) {
                //'false' 블록 끝 (End of 'false' body):
                false_watcher->end = main_watcher->end + 1;
                //범위를 바꾼다 (Change scope):
                materials->scope_type = AIO_IF_WEAVING_SCOPE;
                //메시지 놓다 (Set message):
                spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
                //주요 당직자를 바꾼다 (Shift main watcher):
                main_watcher->start = main_watcher->end + 1;
                main_watcher->mode = POINT_PASSIVE_MODE;
#ifdef AIO_IF_SPIDER_DEBUG
                const_string false_body = substring_by_point_watcher(source_code, false_watcher);
                log_info_string(AIO_IF_SPIDER_TAG, "False body:", false_body);
                log_info(AIO_IF_SPIDER_TAG, "False body is exist. Prepare to weave...");
                free((void *) false_body);
#endif
            }
        }
    }
    //'false' 블록전 공백들을 건너 뛰다 (Skip whitespaces before false body):
    if (!is_whitespace_cond && false_watcher->mode == POINT_PASSIVE_MODE) {
        throw_error_with_tag(AIO_IF_SPIDER_TAG, "Invalid context before false body!");
    }
}

/**
 * Weaving.
 */

void weave_if_instruction_for(aio_instruction_holder *holder, const_string source_code,
                              point_watcher *ripper_watcher, aio_spider *spider) {
#ifdef AIO_IF_SPIDER_DEBUG
    log_info(AIO_IF_SPIDER_TAG, "Start weaving...");
#endif
    //재료들을 추출하다 (Extract materials):
    const aio_if_materials *materials = spider->get.if_materials;
    point_watcher *true_watcher = materials->true_watcher;
    point_watcher *false_watcher = materials->false_watcher;
    const aio_if_branch_type branch_type = materials->branch_type;
    const_boolean is_ready_for_weaving = materials->scope_type == AIO_IF_WEAVING_SCOPE;
    if (is_ready_for_weaving) {
        const_string if_condition = new_string(materials->condition);
        aio_instruction_holder *true_holder = NULL;
        aio_instruction_holder *false_holder = NULL;
#ifdef AIO_IF_SPIDER_DEBUG
        const_string true_body = substring_by_point_watcher(source_code, true_watcher);
        log_info_string(AIO_IF_SPIDER_TAG, "Weave true branch!\n", true_body);
        free((void *) true_body);
#endif
        true_holder = dig_new_aio_instruction_holder(source_code, holder, true_watcher->start,
                                                     true_watcher->end);
        if (branch_type == AIO_HAS_TRUE_BRANCH) {
            ripper_watcher->start = true_watcher->end - 1;
            ripper_watcher->pointer = true_watcher->end - 1;
        }
        if (branch_type == AIO_HAS_TRUE_AND_FALSE_BRANCHES) {
#ifdef AIO_IF_SPIDER_DEBUG
            const_string false_body = substring_by_point_watcher(source_code, false_watcher);
            log_info_string(AIO_IF_SPIDER_TAG, "Weave false branch!\n", false_body);
            free((void *) false_body);
#endif
            ripper_watcher->start = false_watcher->end - 1;
            ripper_watcher->pointer = false_watcher->end - 1;
            false_holder = dig_new_aio_instruction_holder(source_code, holder, false_watcher->start,
                                                          false_watcher->end);
        }
        //지침을 짜다 (Weave instruction):
        aio_instruction *if_instruction = new_aio_if_instruction(holder, if_condition, true_holder, false_holder);
        aio_instruction_list *instruction_list = holder->instruction_list;
        add_aio_instruction_in_list(instruction_list, if_instruction);
        //짜다가 완성되었습니다 (Weaving is complete)!
    } else {
        throw_error_with_tag(AIO_IF_SPIDER_TAG, "Not ready for weaving!");
    }
}