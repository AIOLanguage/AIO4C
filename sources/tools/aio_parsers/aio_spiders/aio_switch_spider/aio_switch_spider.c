#include <malloc.h>
#include <ctype.h>
#include "../../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../headers/tools/aio_parsers/aio_spiders/aio_spider.h"
#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/lib/utils/char_utils/char_utils.h"

#define AIO_SWITCH_SPIDER_DEBUG

#define AIO_SWITCH_SPIDER_TAG "AIO_SWITCH_SPIDER"

#ifdef AIO_SWITCH_SPIDER_DEBUG

#include "../../../../../headers/lib/utils/log_utils/log_utils.h"
#include "../../../../../headers/tools/aio_parsers/aio_block_body_explorer/aio_block_body_explorer.h"

#endif

/**
 * Refresh.
 */

void refresh_switch_spider(aio_spider *spider, point_watcher *ripper_watcher) {
    aio_switch_materials *materials = spider->get.switch_materials;
    //Refresh main watcher:
    point_watcher *main_watcher = materials->main_watcher;
    main_watcher->start = ripper_watcher->pointer;
    main_watcher->end = ripper_watcher->pointer;
    main_watcher->mode = POINT_PASSIVE_MODE;
    //Reset:
    materials->scope_type = AIO_SWITCH_MODIFIER_SCOPE;
    materials->case_scope_type = AIO_SWITCH_CASE_VALUE_SCOPE;
    reset_point_watcher(materials->inner_case_watcher);
    reset_point_watcher(materials->header_watcher);
    reset_point_watcher(materials->switch_body_watcher);
    reset_point_watcher(materials->else_watcher);
    string_hook_list *old_case_value_list = materials->case_value_list;
    string_hook_list *old_case_body_list = materials->case_body_list;
    materials->case_value_list = new_string_hook_list();
    materials->case_body_list = new_string_hook_list();
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_string_hooks_in_list(old_case_value_list);
    free_string_hooks_in_list(old_case_body_list);
    free_string_hook_list(old_case_value_list);
    free_string_hook_list(old_case_body_list);
}

/**
 * Free spider.
 */

void free_switch_spider(aio_spider *spider) {
    aio_switch_materials *materials = spider->get.switch_materials;
    free_point_watcher(materials->main_watcher);
    free_point_watcher(materials->header_watcher);
    free_point_watcher(materials->inner_case_watcher);
    free_point_watcher(materials->switch_body_watcher);
    free_point_watcher(materials->else_watcher);
    string_hook_list *old_case_value_list = materials->case_value_list;
    string_hook_list *old_case_body_list = materials->case_body_list;
    free_string_hooks_in_list(old_case_value_list);
    free_string_hooks_in_list(old_case_body_list);
    free_string_hook_list(old_case_value_list);
    free_string_hook_list(old_case_body_list);
    free(materials);
    free(spider);
}

struct aio_spider *new_aio_switch_spider(point_watcher *ripper_watcher) {
    aio_spider *spider = new_object(sizeof(struct aio_spider));
    //함수들을 놓다 (Put functions):
    spider->refresh = refresh_switch_spider;
    spider->is_found_instruction = is_found_switch_instruction;
    spider->weave_instruction_for = weave_switch_instruction_for;
    spider->free = free_switch_spider;
    //재료들을 만들다 (Create materials);
    aio_switch_materials *materials = new_object(sizeof(struct aio_switch_materials));
    //Init states:
    materials->scope_type = AIO_SWITCH_MODIFIER_SCOPE;
    materials->case_scope_type = AIO_SWITCH_CASE_VALUE_SCOPE;
    materials->has_else_branch = FALSE;
    //Init tools:
    materials->main_watcher = new_point_watcher();
    materials->main_watcher->start = ripper_watcher->start;
    materials->main_watcher->end = ripper_watcher->pointer;
    materials->header_watcher = new_point_watcher();
    materials->inner_case_watcher = new_point_watcher();
    materials->switch_body_watcher = new_point_watcher();
    materials->else_watcher = new_point_watcher();
    materials->case_value_list = new_string_hook_list();
    materials->case_body_list = new_string_hook_list();
    spider->get.switch_materials = materials;
    //시작 메시지를 놓다 (Set start message):
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    return spider;
}

const enum aio_spider_message is_found_switch_instruction(const_string source_code, point_watcher *ripper_watcher,
                                                          struct aio_spider *spider) {
    const aio_switch_materials *materials = spider->get.switch_materials;
    point_watcher *main_watcher = materials->main_watcher;
    main_watcher->end = ripper_watcher->pointer;
    //Define current symbol:
    const char current_symbol = source_code[main_watcher->end];
    //FIXME: Code duplication:
    if (main_watcher->mode == POINT_PASSIVE_MODE) {
        if (is_space_or_line_break(current_symbol)) {
            main_watcher->start++;
        } else {
            main_watcher->mode = POINT_ACTIVE_MODE;
        }
    }
    if (main_watcher->mode == POINT_ACTIVE_MODE) {
        if (materials->scope_type == AIO_SWITCH_MODIFIER_SCOPE) {
            handle_switch_modifier_scope(source_code, spider);
        }
        if (materials->scope_type == AIO_SWITCH_HEADER_SCOPE) {
            handle_switch_header_scope(source_code, spider);
        }
        if (materials->scope_type == AIO_SWITCH_BODY_SCOPE) {
            handle_switch_body_scope(source_code, spider);
        }
    }
    return spider->message;
}

void handle_switch_modifier_scope(const_string source_code, struct aio_spider *spider) {
    aio_switch_materials *materials = spider->get.switch_materials;
    point_watcher *main_watcher = materials->main_watcher;
    const int current_position = main_watcher->end;
    const char current_symbol = source_code[current_position];
    //현재 기호를 확인하다 (Check current symbol):
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    const_boolean is_open_parenthesis_cond = is_opening_parenthesis(current_symbol);
    if (is_whitespace_cond || is_open_parenthesis_cond) {
        const int start_index = main_watcher->start;
        const int hold_positions = current_position - start_index;
        if (hold_positions == 3) {
            const_boolean is_switch_modifier = source_code[start_index] == 'w'
                                               && source_code[start_index + 1] == 'h'
                                               && source_code[start_index + 2] == 'e';
            if (is_switch_modifier) {
                //주요 당직자를 바꾼다 (Shift main watcher):
                main_watcher->start = current_position;
                main_watcher->mode = POINT_PASSIVE_MODE;
                //범위를 바꾼다 (Change scope):
                materials->scope_type = AIO_SWITCH_HEADER_SCOPE;
                //메시지 놓다 (Set message):
                spider->message = AIO_SPIDER_FOUND_MATERIALS;
#ifdef AIO_SWITCH_SPIDER_DEBUG
                log_info(AIO_SWITCH_SPIDER_TAG, "Pass modifier scope!");
#endif
            }
        }
    }
}

void handle_switch_header_scope(const_string source_code, struct aio_spider *spider) {
    aio_switch_materials *materials = spider->get.switch_materials;
    point_watcher *main_watcher = materials->main_watcher;
    point_watcher *header_watcher = materials->header_watcher;
    int start_index = main_watcher->start;
    int end_index = 0;
#ifdef AIO_SWITCH_SPIDER_DEBUG
    log_info(AIO_SWITCH_SPIDER_TAG, "Explore switch header...");
#endif
    explore_header_body(source_code, &start_index, &end_index);
    //Set positions in header watcher:
    header_watcher->start = start_index;
    header_watcher->end = end_index;
#ifdef AIO_SWITCH_SPIDER_DEBUG
    const_string header = substring_by_point_watcher(source_code, header_watcher);
    log_info_string(AIO_SWITCH_SPIDER_TAG, "Captured header:", header);
    free((void *) header);
#endif
    //Shift main watcher:
    main_watcher->start = end_index;
    main_watcher->end = end_index;
    //Go to the next scope:
    materials->scope_type = AIO_SWITCH_BODY_SCOPE;
}

void handle_switch_body_scope(const_string source_code, struct aio_spider *spider) {
    aio_switch_materials *materials = spider->get.switch_materials;
    point_watcher *main_watcher = materials->main_watcher;
    point_watcher *body_watcher = materials->switch_body_watcher;
    int start_index = main_watcher->start;
    int end_index = 0;
#ifdef AIO_SWITCH_SPIDER_DEBUG
    log_info(AIO_SWITCH_SPIDER_TAG, "Explore switch body");
#endif
    explore_block_body(source_code, &start_index, &end_index);
    body_watcher->start = start_index;
    body_watcher->end = end_index;
#ifdef AIO_SWITCH_SPIDER_DEBUG
    const_string chunk = substring_by_point_watcher(source_code, body_watcher);
    log_info_string(AIO_SWITCH_SPIDER_TAG, "Captured switch body:", chunk);
    free((void *) chunk);
#endif
    //Build cases:
    build_switch_cases(source_code, spider);
    //Check else branch:
    while (is_space_or_line_break(source_code[end_index])) {
        end_index++;
    }
    if (is_colon(source_code[end_index])) {
        //Default branch is exist!
        start_index = end_index + 1;
        end_index = 0;
        explore_block_body(source_code, &start_index, &end_index);
        point_watcher *else_watcher = materials->else_watcher;
        else_watcher->start = start_index;
        else_watcher->end = end_index;
#ifdef AIO_SWITCH_SPIDER_DEBUG
        const_string else_chunk = substring_by_point_watcher(source_code, else_watcher);
        log_info_string(AIO_SWITCH_SPIDER_TAG, "Captured else body:", else_chunk);
        free((void *) else_chunk);
#endif
        materials->has_else_branch = TRUE;
    }
    main_watcher->start = end_index;
    main_watcher->end = end_index;
    materials->scope_type = AIO_SWITCH_WEAVING_SCOPE;
    spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
}

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//CASE BUILDING START:

void build_switch_cases(const_string source_code, aio_spider *spider) {
    aio_switch_materials *materials = spider->get.switch_materials;
    point_watcher *body_watcher = materials->switch_body_watcher;
    //Without braces:
    const int start = ++body_watcher->start;
    const int end = body_watcher->end - 1;
    for (body_watcher->pointer = start; body_watcher->pointer < end; ++body_watcher->pointer) {
        const_boolean is_not_whitespace_cond = !is_space_or_line_break(source_code[body_watcher->pointer]);
        if (body_watcher->mode == POINT_PASSIVE_MODE && is_not_whitespace_cond) {
            //Create new string_hook:
            body_watcher->mode = POINT_ACTIVE_MODE;
        }
        if (body_watcher->mode == POINT_ACTIVE_MODE) {
            if (materials->case_scope_type == AIO_SWITCH_CASE_VALUE_SCOPE) {
                handle_switch_case_value_scope(source_code, spider);
                return;
            }
            if (materials->case_scope_type == AIO_SWITCH_CASE_BODY_SCOPE) {
                handle_switch_case_body_scope(source_code, spider);
            }
        }
    }
}

const_boolean is_pointer(const_string source_code, const int current_position) {
    return source_code[current_position - 1] == '-'
           && source_code[current_position] == '>';
}

void handle_switch_case_value_scope(const_string source_code, aio_spider *spider) {
    //재료들을 추출하다 (Extract materials):
    aio_switch_materials *materials = spider->get.switch_materials;
    point_watcher *body_watcher = materials->switch_body_watcher;
    while (!is_pointer(source_code, body_watcher->pointer)) {
        body_watcher->pointer++;
    }
    //Put case value bounds in list & don't hold pointer::
    string_hook *hook = new_string_hook_with_start_and_end(source_code, body_watcher->start, body_watcher->pointer - 1);
#ifdef AIO_SWITCH_SPIDER_DEBUG
    const_string case_value = substring_by_string_hook(hook);
    log_info_string(AIO_SWITCH_SPIDER_TAG, "Captured case value:", case_value);
    free((void *) case_value);
#endif
    add_string_hook_in_list(materials->case_value_list, hook);
    //Prepare to go to next scope:
    body_watcher->start = body_watcher->pointer;
    body_watcher->mode = POINT_PASSIVE_MODE;
    materials->case_scope_type = AIO_SWITCH_CASE_BODY_SCOPE;
}

void handle_is_last_case_condition(const_boolean is_last_case, aio_spider *spider) {
    aio_switch_materials *materials = spider->get.switch_materials;
    if (is_last_case) {
        //위빙 준비 (Prepare for weaving):
        materials->scope_type = AIO_SWITCH_WEAVING_SCOPE;
        spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
#ifdef AIO_SWITCH_SPIDER_DEBUG
        log_info(AIO_SWITCH_SPIDER_TAG, "Was last case...");
#endif
    } else {
        materials->case_scope_type = AIO_SWITCH_CASE_VALUE_SCOPE;
        log_info(AIO_SWITCH_SPIDER_TAG, "Will find more cases...");
    }
}

void handle_switch_case_body_scope(const_string source_code, aio_spider *spider) {
    aio_switch_materials *materials = spider->get.switch_materials;
    point_watcher *body_watcher = materials->switch_body_watcher;
    //Define current symbol:
    const int current_position = body_watcher->pointer;
    //Check symbol:
    int start_index = current_position;
    int end_index = 0;
    if (is_opening_brace(source_code[current_position])) {
        explore_block_body(source_code, &start_index, &end_index);
        //Put body bounds in list:
        string_hook *hook = new_string_hook_with_start_and_end(source_code, start_index, end_index);
        add_string_hook_in_list(materials->case_body_list, hook);
        const_boolean is_last_case = end_index == body_watcher->end;
        handle_is_last_case_condition(is_last_case, spider);
    } else {
        point_watcher *case_watcher = materials->inner_case_watcher;
        for (int i = start_index; i < body_watcher->end; ++i) {
            const char current_symbol = source_code[i];
            //Check symbol:
            const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
            const_boolean is_close_parenthesis_cond = is_closing_parenthesis(current_symbol);
            const_boolean is_letter_cond = isalpha(current_symbol);
            const_boolean is_letter_or_number_or_close_parenthesis_cond = isalnum(current_symbol)
                                                                          || is_close_parenthesis_cond;
            const_boolean is_close_brace_cond = is_closing_brace(current_symbol);
            if (is_whitespace_cond && case_watcher->mode == POINT_ACTIVE_MODE) {
                case_watcher->pointer++;
                continue;
            }
            const_boolean is_next_case = is_letter_cond && case_watcher->pointer > 0;
            const_boolean is_last_case = is_close_brace_cond && i == body_watcher->end - 1;
            if ((is_next_case || is_last_case)
                && case_watcher->mode == POINT_ACTIVE_MODE) {
                case_watcher->start = start_index;
                case_watcher->end = i - case_watcher->pointer;
                //Add case body hook in list:
                string_hook *hook = new_string_hook_by_point_watcher(source_code, case_watcher);
                add_string_hook_in_list(materials->case_body_list, hook);
#ifdef AIO_SWITCH_SPIDER_DEBUG
                const_string chunk = substring_by_string_hook(hook);
                log_info_string(AIO_SWITCH_SPIDER_TAG, "Captured case body:", chunk);
                free((void *) chunk);
#endif
                handle_is_last_case_condition(is_last_case, spider);
            } else {
                case_watcher->mode = POINT_PASSIVE_MODE;
                case_watcher->pointer = 0;
                if (is_letter_or_number_or_close_parenthesis_cond) {
                    case_watcher->mode = POINT_ACTIVE_MODE;
                }
            }
        }
    }
}

//CASE BUILDING END:
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------


void weave_switch_instruction_for(aio_instruction_holder *holder, const_string source_code,
                                  point_watcher *ripper_watcher, struct aio_spider *spider) {
//#ifdef AIO_PROCEDURE_SPIDER_DEBUG
//    log_info(AIO_PROCEDURE_SPIDER_TAG, "Start weaving...");
//#endif
//    //재료들을 추출하다 (Extract materials):
//    const aio_procedure_materials *materials = spider->get.procedure_materials;
//    const point_watcher *watcher = materials->main_watcher;
//    //Change ripper_watcher:
//    const int new_point = watcher->end;
//    ripper_watcher->pointer = new_point;
//    ripper_watcher->start = new_point;
//    string dirty_expression = substring_by_point_watcher(source_code, watcher);
//    string clean_expression = squeeze_string(dirty_expression);
//#ifdef AIO_PROCEDURE_SPIDER_DEBUG
//    log_info_string(AIO_PROCEDURE_SPIDER_TAG, "CAPTURED EXPRESSION:", clean_expression);
//#endif
//    aio_instruction *procedure_instruction = new_aio_procedure_instruction(holder, clean_expression);
//    //명부에게 지침을 추가하다 (Add 'Procedure' instruction in holder's instructions):
//    aio_instruction_list *instruction_list = holder->instruction_list;
//    add_aio_instruction_in_list(instruction_list, procedure_instruction);
//    //위빙이 완료되었습니다 (Weaving complete)!
//#ifdef AIO_PROCEDURE_SPIDER_DEBUG
//    log_info(AIO_PROCEDURE_SPIDER_TAG, "WEAVED INSTRUCTION:");
//    log_info_string(AIO_PROCEDURE_SPIDER_TAG, "EXPRESSION:", procedure_instruction->get.procedure_task->expression);
//#endif
//    //------------------------------------------------------------------------------------------------------------------
//    //찌거기 수집기 (Garbage collector):
//    free(dirty_expression);
}
