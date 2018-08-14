#include <malloc.h>
#include <mem.h>
#include <ctype.h>
#include "../../../../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../../../headers/lib/point_watcher/point_watcher.h"
#include "../../../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../../../headers/lib/utils/string_utils/string_builder.h"
#include "../../../../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"
#include "../../../../../../../headers/tools/aio_parsers/aio_function_parser/aio_rippers/aio_spiders/aio_spider.h"
#include "../../../../../../../headers/lib/utils/memory_utils/memory_utils.h"

/**
 * 함수들을 선인하다 (Declare functions).
 */

const aio_spider_message is_found_if_instruction(const_string string_web, aio_spider *spider);

void handle_if_modifier_scope(const_string string_web, aio_spider *spider);

void handle_condition_scope(const_string string_web, aio_spider *spider);

void handle_true_body_scope(const_string string_web, aio_spider *spider);

void handle_false_body_scope(const_string string_web, aio_spider *spider);

void weave_if_instruction_for(aio_instruction_holder *holder, const_string source_code,
                              int *next_ripper_point_reference, aio_spider *spider);

/**
 * 주 논리 (Business logic).
 */

#define AIO_IF_SPIDER_DEBUG

#define AIO_IF_SPIDER_TAG "AIO_IF_SPIDER"

#ifdef AIO_IF_SPIDER_DEBUG

#include "../../../../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

/**
 * 레셋 (Reset).
 */

void reset_if_spider(aio_spider *spider) {
    //거미의 조건 리셋 (Reset spider state):
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    //재료 리셋 (Reset materials):
    aio_if_materials *materials = spider->get.if_materials;
    reset_point_watcher(materials->main_watcher);
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

aio_spider *new_aio_if_spider() {
    aio_spider *spider = new_object(sizeof(aio_spider));
    //함수들을 놓다 (Put functions):
    spider->reset = reset_if_spider;
    spider->is_found_instruction = is_found_if_instruction;
    spider->weave_instruction_for = weave_if_instruction_for;
    spider->free = free_if_spider;
    //재료들을 만들다 (Create materials):
    aio_if_materials *materials = new_object(sizeof(aio_if_materials));
    materials->main_watcher = new_point_watcher();
    materials->header_watcher = new_point_watcher();
    materials->true_watcher = new_point_watcher();
    materials->false_watcher = new_point_watcher();
    //조건들을 놓다 (Set states):
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

const aio_spider_message is_found_if_instruction(const_string string_web, aio_spider *spider) {
    //재료들을 추출하다 (Extract materials):
    const aio_if_materials *materials = spider->get.if_materials;
    point_watcher *main_watcher = materials->main_watcher;
    main_watcher->end_index++;
    //스캐닝 준비 (Prepare for scanning):
    const int current_position = main_watcher->end_index - 1;
    const char current_symbol = string_web[current_position];
    //TODO: 코드 복제 (Code duplication)!
    if (main_watcher->mode == POINT_PASSIVE_MODE) {
        if (is_space_or_line_break(current_symbol)) {
            main_watcher->start_index++;
        } else {
            main_watcher->mode = POINT_ACTIVE_MODE;
        }
    }
    if (main_watcher->mode == POINT_ACTIVE_MODE) {
        if (materials->scope_type == AIO_IF_MODIFIER_SCOPE) {
            handle_if_modifier_scope(string_web, spider);
        }
        if (materials->scope_type == AIO_IF_CONDITION_SCOPE) {
            handle_condition_scope(string_web, spider);
            return spider->message;
        }
        if (materials->scope_type == AIO_IF_TRUE_BODY_SCOPE) {
            handle_true_body_scope(string_web, spider);
            return spider->message;
        }
        if (materials->scope_type == AIO_IF_FALSE_BODY_SCOPE) {
            handle_false_body_scope(string_web, spider);
        }
    }
    return spider->message;
}

void handle_if_modifier_scope(const_string string_web, aio_spider *spider) {
    aio_if_materials *materials = spider->get.if_materials;
    point_watcher *watcher = materials->main_watcher;
    const char current_symbol = string_web[watcher->end_index - 1];
    //현재 기호를 확인하다 (Check current symbol):
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    const_boolean is_open_parenthesis_cond = is_opening_parenthesis(current_symbol);
    if (is_whitespace_cond || is_open_parenthesis_cond) {
        const int start_index = watcher->start_index;
        const int end_index = watcher->end_index;
        const int hold_positions = end_index - start_index;
        if (hold_positions == 3) {
            const_boolean is_if_modifier = string_web[start_index] == 'i' && string_web[start_index + 1] == 'f';
            if (is_if_modifier) {
                //주요 당직자를 바꾼다 (Shift main watcher):
                watcher->start_index = end_index;
                watcher->mode = POINT_PASSIVE_MODE;
                //범위를 바꾼다 (Change scope):
                materials->scope_type = AIO_IF_CONDITION_SCOPE;
                //메시지 놓다 (Set message):
                spider->message = AIO_SPIDER_FOUND_MATERIALS;
            }
        }
    }
}

void handle_condition_scope(const_string string_web, aio_spider *spider) {
    aio_if_materials *materials = spider->get.if_materials;
    point_watcher *main_watcher = materials->main_watcher;
    point_watcher *header_watcher = materials->header_watcher;
    //현재 위치를 정의하다 (Define current position):
    const int current_position = main_watcher->end_index - 1;
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
            header_watcher->start_index = main_watcher->end_index;
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
                header_watcher->end_index = current_position;
                //주요 당직자를 바꾼다 (Shift main watcher):
                main_watcher->start_index = main_watcher->end_index;
                main_watcher->mode = POINT_PASSIVE_MODE;
                //범위를 바꾼다 (Change scope):
                materials->scope_type = AIO_IF_TRUE_BODY_SCOPE;
                //조건을 추출하다 (Extract condition):
                const_string dirty_condition = substring_by_point_watcher(string_web, header_watcher);
                string clean_condition = squeeze_string(dirty_condition);
                materials->condition = clean_condition;
                //------------------------------------------------------------------------------------------------------
                //찌꺼기 수집기 (Garbage collector):
                free((void *) dirty_condition);
            }
        }
        return;
    }
    //조건 전 공백들을 건너 뛰다 (Skip whitespaces before condition):
    if (!is_whitespace_cond && header_watcher->mode == POINT_PASSIVE_MODE) {
        throw_error_with_tag(AIO_IF_SPIDER_TAG, "Invalid context after 'if' modifier!");
    }
}

void handle_true_body_scope(const_string string_web, aio_spider *spider) {
    aio_if_materials *materials = spider->get.if_materials;
    point_watcher *main_watcher = materials->main_watcher;
    point_watcher *true_watcher = materials->true_watcher;
    //Define last position:
    const int current_position = main_watcher->end_index - 1;
    const char current_symbol = string_web[current_position];
    //Scanning:
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    const_boolean is_open_brace_cond = is_opening_brace(current_symbol);
    const_boolean is_close_brace_cond = is_closing_brace(current_symbol);
    const_boolean is_colon_cond = is_colon(current_symbol);
    //Meet open brace:
    if (is_open_brace_cond) {
        //Start of true body:
        if (true_watcher->mode == POINT_PASSIVE_MODE) {
            //Hold open brace:
            true_watcher->start_index = current_position;
            true_watcher->mode = POINT_ACTIVE_MODE;
        }
        //Brace in body:
        if (true_watcher->mode == POINT_ACTIVE_MODE) {
            //Count parentheses:
            true_watcher->pointer++;
        }
    }
    //Meet close brace:
    if (is_close_brace_cond) {
        //Doesn't start body:
        if (true_watcher->mode == POINT_PASSIVE_MODE) {
            throw_error_with_tag(AIO_IF_SPIDER_TAG, "True body can not start with close brace!");
        }
        //In true body:
        if (true_watcher->mode == POINT_ACTIVE_MODE) {
            true_watcher->pointer--;
            //Brace closes true body:
            if (true_watcher->pointer == 0) {
                //End of true body:
                //Hold close brace:
                true_watcher->end_index = main_watcher->end_index;
                true_watcher->mode = POINT_UNDEFINED_MODE;
#ifdef AIO_IF_SPIDER_DEBUG
                const_string true_body = substring_by_point_watcher(string_web, true_watcher);
                log_info_string(AIO_IF_SPIDER_TAG, "True body:", true_body);
                free((void *) true_body);
#endif
                return;
            }
        }
    }
    //Skip whitespaces after condition:
    if (!is_whitespace_cond) {
        if (true_watcher->mode == POINT_PASSIVE_MODE) {
            throw_error_with_tag(AIO_IF_SPIDER_TAG, "Invalid context after 'if' condition!");
        }
        //Waiting false modifier or other symbol:
        if (true_watcher->mode == POINT_UNDEFINED_MODE) {
            //If meet colon then this is 'false' modifier:
            if (is_colon_cond) {
                //Set branch type:
                materials->branch_type = AIO_HAS_TRUE_AND_FALSE_BRANCHES;
                //Set scope:
                materials->scope_type = AIO_IF_FALSE_BODY_SCOPE;
#ifdef AIO_IF_SPIDER_DEBUG
                log_info(AIO_IF_SPIDER_TAG, "Prepare to find false body...!");
#endif
            } else {
                //Set branch type:
                materials->branch_type = AIO_HAS_TRUE_BRANCH;
                //Set scope:
                materials->scope_type = AIO_IF_WEAVING_SCOPE;
                //Set message:
                spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
#ifdef AIO_IF_SPIDER_DEBUG
                log_info(AIO_IF_SPIDER_TAG, "False body is absent! Prepare to weave...");
#endif
            }
            //Shift main main_watcher:
            main_watcher->start_index = main_watcher->end_index;
            main_watcher->mode = POINT_PASSIVE_MODE;
        }
    }
}

void handle_false_body_scope(const_string string_web, aio_spider *spider) {
    aio_if_materials *materials = spider->get.if_materials;
    point_watcher *main_watcher = materials->main_watcher;
    point_watcher *false_watcher = materials->false_watcher;
    //Define last position:
    const int current_position = main_watcher->end_index - 1;
    const char current_symbol = string_web[current_position];
    //Scanning:
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    const_boolean is_open_brace_cond = is_opening_brace(current_symbol);
    const_boolean is_close_brace_cond = is_closing_brace(current_symbol);
    //Meet open brace:
    if (is_open_brace_cond) {
        //Start of true body:
        if (false_watcher->mode == POINT_PASSIVE_MODE) {
            //Hold open brace:
            false_watcher->start_index = current_position;
            false_watcher->mode = POINT_ACTIVE_MODE;
        }
        //Brace in body:
        if (false_watcher->mode == POINT_ACTIVE_MODE) {
            //Count parentheses:
            false_watcher->pointer++;
        }
    }
    //Meet close brace:
    if (is_close_brace_cond) {
        //Doesn't start body:
        if (false_watcher->mode == POINT_PASSIVE_MODE) {
            throw_error_with_tag(AIO_IF_SPIDER_TAG, "False body can not start with close brace!");
        }
        //In true body:
        if (false_watcher->mode == POINT_ACTIVE_MODE) {
            false_watcher->pointer--;
            //Brace closes true body:
            if (false_watcher->pointer == 0) {
                //End of true body:
                false_watcher->end_index = main_watcher->end_index;
                //Set scope:
                materials->scope_type = AIO_IF_WEAVING_SCOPE;
                //Set message:
                spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
                //Shift main main_watcher:
                main_watcher->start_index = main_watcher->end_index;
                main_watcher->mode = POINT_PASSIVE_MODE;
#ifdef AIO_IF_SPIDER_DEBUG
                const_string false_body = substring_by_point_watcher(string_web, false_watcher);
                log_info_string(AIO_IF_SPIDER_TAG, "False body:", false_body);
                log_info(AIO_IF_SPIDER_TAG, "False body is exist. Prepare to weave...");
                free((void *) false_body);
#endif
            }
        }
    }
    //Skip whitespaces before false body:
    if (!is_whitespace_cond && false_watcher->mode == POINT_PASSIVE_MODE) {
        throw_error_with_tag(AIO_IF_SPIDER_TAG, "Invalid context before false body!");
    }
}

/**
 * Weaving.
 */

void weave_if_instruction_for(aio_instruction_holder *holder, const_string source_code,
                              int *next_ripper_point_reference, aio_spider *spider) {
#ifdef AIO_IF_SPIDER_DEBUG
    log_info(AIO_IF_SPIDER_TAG, "Start weaving...");
#endif
    //Extract spider fields:
    const aio_if_materials *materials = spider->get.if_materials;
    const point_watcher *main_watcher = materials->main_watcher;
    const point_watcher *true_watcher = materials->true_watcher;
    const point_watcher *false_watcher = materials->false_watcher;
    const aio_if_branch_type branch_type = materials->branch_type;
    const_boolean is_ready_for_weaving = materials->scope_type == AIO_IF_WEAVING_SCOPE;
    if (is_ready_for_weaving) {
        //Weave if instruction:
        const_string if_condition = new_string(materials->condition);
        aio_instruction_holder *true_holder = NULL;
        aio_instruction_holder *false_holder = NULL;
        int start_position = *next_ripper_point_reference + true_watcher->start_index + 1;
        int end_position = *next_ripper_point_reference + true_watcher->end_index + 1;
#ifdef AIO_IF_SPIDER_DEBUG
        const_string true_body = substring(source_code, start_position, end_position);
        log_info_string(AIO_IF_SPIDER_TAG, "Weave true branch!\n", true_body);
        free((void *) true_body);
#endif
        true_holder = dig_aio_instruction_holder(source_code, holder, start_position, end_position);
        if (branch_type == AIO_HAS_TRUE_AND_FALSE_BRANCHES) {
            start_position = *next_ripper_point_reference + false_watcher->start_index + 1;
            end_position = *next_ripper_point_reference + false_watcher->end_index + 1;
#ifdef AIO_IF_SPIDER_DEBUG
            const_string false_body = substring(source_code, start_position, end_position);
            log_info_string(AIO_IF_SPIDER_TAG, "Weave false branch!\n", false_body);
            free((void *) false_body);
#endif
            false_holder = dig_aio_instruction_holder(source_code, holder, start_position, end_position);
        }
        //Weave instruction:
        aio_instruction *if_instruction = new_aio_if_instruction(holder, if_condition, true_holder, false_holder);
        //Add if instruction in holder's instructions:
        aio_instruction_list *instruction_list = holder->instruction_list;
        add_aio_instruction_in_list(instruction_list, if_instruction);
        //Weaving complete!
        *next_ripper_point_reference += main_watcher->end_index;
    } else {
        throw_error_with_tag(AIO_IF_SPIDER_TAG, "Not ready for weaving!");
    }
}