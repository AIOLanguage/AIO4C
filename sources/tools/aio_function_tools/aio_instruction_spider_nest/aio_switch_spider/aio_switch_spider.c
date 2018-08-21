#include <malloc.h>
#include <ctype.h>
#include <process.h>
#include "../../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../headers/tools/aio_common_tools/aio_spider_nest/aio_spider.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instruction_spider_nest/aio_switch_spider/aio_switch_spider.h"
#include "../../../../../headers/lib/utils/str_hook/str_hook.h"
#include "../../../../../headers/tools/aio_common_tools/aio_block_body_explorer/aio_block_body_explorer.h"
#include "../../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction_holder.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_switch_task.h"

#define AIO_SWITCH_SPIDER_DEBUG

#define AIO_SWITCH_SPIDER_TAG "AIO_SWITCH_SPIDER"

#ifdef AIO_SWITCH_SPIDER_DEBUG

#include "../../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

/**
 * Refresh.
 */

void refresh_switch_spider(aio_spider *spider, point_watcher *ripper_watcher) {
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    aio_switch_materials *materials = spider->materials;
    //Refresh main watcher:
    point_watcher *main_watcher = materials->main_watcher;
    main_watcher->start = ripper_watcher->pointer;
    main_watcher->end = ripper_watcher->pointer;
    main_watcher->mode = POINT_WATCHER_PASSIVE_MODE;
    //Reset:
    materials->scope_type = AIO_SWITCH_MODIFIER_SCOPE;
    reset_point_watcher(materials->header_watcher);
    reset_point_watcher(materials->switch_body_watcher);
    reset_point_watcher(materials->else_watcher);
    str_hook_list *old_case_value_list = materials->case_key_list;
    str_hook_list *old_case_body_list = materials->case_body_list;
    materials->case_key_list = new_str_hook_list();
    materials->case_body_list = new_str_hook_list();
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_str_hooks_in_list(old_case_value_list);
    free_str_hooks_in_list(old_case_body_list);
    free_str_hook_list(old_case_value_list);
    free_str_hook_list(old_case_body_list);
}

/**
 * Free spider.
 */

void free_switch_spider(aio_spider *spider) {
    aio_switch_materials *materials = spider->materials;
    free_point_watcher(materials->main_watcher);
    free_point_watcher(materials->header_watcher);
    free_point_watcher(materials->switch_body_watcher);
    free_point_watcher(materials->else_watcher);
    str_hook_list *old_case_value_list = materials->case_key_list;
    str_hook_list *old_case_body_list = materials->case_body_list;
    free_str_hooks_in_list(old_case_value_list);
    free_str_hooks_in_list(old_case_body_list);
    free_str_hook_list(old_case_value_list);
    free_str_hook_list(old_case_body_list);
    free(materials);
    free(spider);
}

struct aio_spider *new_aio_switch_spider(point_watcher *ripper_watcher) {
    aio_spider *spider = new_object(sizeof(struct aio_spider));
    //함수들을 놓다 (Put functions):
    spider->refresh = refresh_switch_spider;
    spider->is_found_context = is_found_switch_instruction;
    spider->weave_context_for = weave_switch_instruction_for;
    spider->free = free_switch_spider;
    //재료들을 만들다 (Create materials);
    aio_switch_materials *materials = new_object(sizeof(struct aio_switch_materials));
    //Init states:
    materials->scope_type = AIO_SWITCH_MODIFIER_SCOPE;
    materials->has_else_branch = FALSE;
    //Init tools:
    materials->main_watcher = new_point_watcher();
    materials->main_watcher->start = ripper_watcher->start;
    materials->main_watcher->end = ripper_watcher->pointer;
    materials->header_watcher = new_point_watcher();
    materials->switch_body_watcher = new_point_watcher();
    materials->else_watcher = new_point_watcher();
    materials->case_key_list = new_str_hook_list();
    materials->case_body_list = new_str_hook_list();
    spider->materials = materials;
    //시작 메시지를 놓다 (Set start message):
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    return spider;
}

const enum aio_spider_message is_found_switch_instruction(const_string source_code, point_watcher *ripper_watcher,
                                                          struct aio_spider *spider) {
    const aio_switch_materials *materials = spider->materials;
    point_watcher *main_watcher = materials->main_watcher;
    main_watcher->end = ripper_watcher->pointer;
    //Define current symbol:
    const char current_symbol = source_code[main_watcher->end];
    //FIXME: Code duplication:
    if (main_watcher->mode == POINT_WATCHER_PASSIVE_MODE) {
        if (is_space_or_line_break(current_symbol)) {
            main_watcher->start++;
        } else {
            main_watcher->mode = POINT_WATCHER_ACTIVE_MODE;
        }
    }
    if (main_watcher->mode == POINT_WATCHER_ACTIVE_MODE) {
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
    aio_switch_materials *materials = spider->materials;
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
                main_watcher->mode = POINT_WATCHER_PASSIVE_MODE;
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
    aio_switch_materials *materials = spider->materials;
    point_watcher *main_watcher = materials->main_watcher;
    point_watcher *header_watcher = materials->header_watcher;
    int start_index = main_watcher->start;
    int end_index = 0;
#ifdef AIO_SWITCH_SPIDER_DEBUG
    log_info(AIO_SWITCH_SPIDER_TAG, "Explore switch header...");
#endif
    explore_aio_header_bounds(source_code, &start_index, &end_index);
    //Set positions in header watcher:
    header_watcher->start = start_index + 1;
    header_watcher->end = end_index - 1;
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
    aio_switch_materials *materials = spider->materials;
    point_watcher *main_watcher = materials->main_watcher;
    point_watcher *switch_body_watcher = materials->switch_body_watcher;
    int start_index = main_watcher->start;
    int end_index = 0;
#ifdef AIO_SWITCH_SPIDER_DEBUG
    log_info(AIO_SWITCH_SPIDER_TAG, "Explore switch body");
#endif
    explore_aio_block_bounds(source_code, &start_index, &end_index);
    switch_body_watcher->start = start_index;
    switch_body_watcher->end = end_index;
#ifdef AIO_SWITCH_SPIDER_DEBUG
    const_string chunk = substring_by_point_watcher(source_code, switch_body_watcher);
    log_info_string(AIO_SWITCH_SPIDER_TAG, "Captured switch body:", chunk);
    free((void *) chunk);
#endif
    //Build cases:
    build_switch_cases(source_code, spider);
    //Check else branch:
    while (is_space_or_line_break(source_code[end_index])) {
        end_index++;
    }
    const_boolean has_else_branch = is_colon(source_code[end_index]);
    if (has_else_branch) {
        //Default branch is exist!
        start_index = end_index + 1;
        end_index = 0;
        explore_aio_block_bounds(source_code, &start_index, &end_index);
        point_watcher *else_watcher = materials->else_watcher;
        else_watcher->start = start_index;
        else_watcher->end = end_index;
#ifdef AIO_SWITCH_SPIDER_DEBUG
        const_string else_chunk = substring_by_point_watcher(source_code, else_watcher);
        log_info_string(AIO_SWITCH_SPIDER_TAG, "Captured else body:", else_chunk);
        free((void *) else_chunk);
#endif
        materials->has_else_branch = TRUE;
    } else {
        //Body watcher will need in weaving:
        switch_body_watcher->start = start_index;
        switch_body_watcher->end = end_index;
    }
    main_watcher->start = end_index;
    main_watcher->end = end_index;
    materials->scope_type = AIO_SWITCH_WEAVING_SCOPE;
    spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
}

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//CASE BUILDING START:

const_boolean is_pointer(const_string source_code, const int current_position) {
    return source_code[current_position - 1] == '-'
           && source_code[current_position] == '>';
}

void build_switch_cases(const_string source_code, aio_spider *spider) {
    aio_switch_materials *materials = spider->materials;
    str_hook_list *case_key_list = materials->case_key_list;
    str_hook_list *case_body_list = materials->case_body_list;
    //Get switch body watcher:
    point_watcher *body_watcher = materials->switch_body_watcher;
    //Without braces:
    const int start = ++body_watcher->start;
    const int end = body_watcher->end - 1;
    for (body_watcher->pointer = start; body_watcher->pointer < end; ++body_watcher->pointer) {
        const_boolean is_not_whitespace_cond = !is_space_or_line_break(source_code[body_watcher->pointer]);
        if (body_watcher->mode == POINT_WATCHER_PASSIVE_MODE && is_not_whitespace_cond) {
            body_watcher->mode = POINT_WATCHER_ACTIVE_MODE;
        }
        //Find case:
        if (body_watcher->mode == POINT_WATCHER_ACTIVE_MODE) {
            boolean has_string_content = FALSE;
            while (!is_pointer(source_code, body_watcher->pointer)) {
                if (isalnum(source_code[body_watcher->pointer])) {
                    has_string_content = TRUE;
                }
                body_watcher->pointer++;
            }
            if (!has_string_content) {
                throw_error_with_tag(AIO_SWITCH_SPIDER_TAG, "Invalid case key in switch body!");
            }
            //Put case value bounds in list & don't hold pointer::
            body_watcher->end = body_watcher->pointer - 1;
            str_hook *key_hook = new_str_hook_by_point_watcher(source_code, body_watcher);
#ifdef AIO_SWITCH_SPIDER_DEBUG
            log_info_str_hook(AIO_SWITCH_SPIDER_TAG, "Captured case key:", key_hook);
#endif
            add_str_hook_in_list(case_key_list, key_hook);
            //Prepare to find case body:
            body_watcher->start = ++body_watcher->pointer;
            //Take start & end indexes again:
            explore_aio_block_bounds(source_code, &body_watcher->start, &body_watcher->end);
            //Put body bounds in list:
            str_hook *body_hook = new_str_hook_by_point_watcher(source_code, body_watcher);
#ifdef AIO_SWITCH_SPIDER_DEBUG
            log_info_str_hook(AIO_SWITCH_SPIDER_TAG, "Captured case body:", body_hook);
#endif
            add_str_hook_in_list(case_body_list, body_hook);
            body_watcher->start = body_watcher->end;
            body_watcher->pointer = body_watcher->end;
            body_watcher->end = end;
            const_boolean is_last_case = has_context_rest(source_code, body_watcher);
            const_boolean is_found_cases_by_pairs = case_key_list->size == case_body_list->size;
            if (is_last_case && is_found_cases_by_pairs) {
                //위빙 준비 (Prepare for weaving):
                materials->scope_type = AIO_SWITCH_WEAVING_SCOPE;
                spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
#ifdef AIO_SWITCH_SPIDER_DEBUG
                log_info(AIO_SWITCH_SPIDER_TAG, "Was last case...");
#endif
                break;
            }
        }
    }
}

//CASE BUILDING END:
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

void weave_switch_instruction_for(void *parent, const_string source_code,
                                  point_watcher *ripper_watcher, struct aio_spider *spider) {
    aio_function_instruction_holder *holder = parent;
#ifdef AIO_SWITCH_SPIDER_DEBUG
    log_info(AIO_SWITCH_SPIDER_TAG, "Start weaving...");
#endif
    //재료들을 추출하다 (Extract materials):
    const aio_switch_materials *materials = spider->materials;
    const_str_hook_list *case_key_hooks = materials->case_key_list;
    const_str_hook_list *case_body_hooks = materials->case_body_list;
    const_point_watcher *body_watcher = materials->switch_body_watcher;
    const_point_watcher *header_watcher = materials->header_watcher;
    //Create holders:
    aio_function_instruction_holder *new_else_holder = NULL;
    //Create switch holders:
    const size_t number_of_case_hooks = (const size_t) case_key_hooks->size;
    //Put all cases in general array of lists:
    string_list **general_case_lists = new_object_array(number_of_case_hooks, sizeof(string_list *));
    unsigned int number_of_cases = 0;
    for (int i = 0; i < number_of_case_hooks; ++i) {
        const_str_hook *case_keys_hook = case_key_hooks->hooks[i];
        //Hook mays contain several case keys:
        string_list *case_key_list = extract_case_keys_from_hook(case_keys_hook);
        number_of_cases += case_key_list->size;
        general_case_lists[i] = case_key_list;
    }
#ifdef AIO_SWITCH_SPIDER_DEBUG
    log_info_int(AIO_SWITCH_SPIDER_TAG, "NUMBER OF CASES:", number_of_cases);
#endif
    //Init case holder array:
    aio_function_instruction_holder **new_case_holders
            = new_object_array(number_of_cases, sizeof(aio_function_instruction_holder *));
    string_list *new_case_key_list = new_string_list();
    int index = 0;
    for (int k = 0; k < number_of_case_hooks; ++k) {
        const_str_hook *body_hook = case_body_hooks->hooks[k];
        const int start = body_hook->start;
        const int end = body_hook->end;
        string_list *case_key_list = general_case_lists[k];
        const int list_size = case_key_list->size;
        for (int i = 0; i < list_size; ++i) {
            //Put "list_size" times case holder in array:
            aio_function_instruction_holder *new_holder
                    = inflate_local_aio_instruction_holder(source_code, parent, start, end);
            new_case_holders[index++] = new_holder;
            add_string_in_list(new_case_key_list, case_key_list->strings[i]);
        }
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free_string_list(case_key_list);
    }
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free(general_case_lists);
    //------------------------------------------------------------------------------------------------------------------
    int new_point = 0;
    const_boolean has_else_branch = materials->has_else_branch;
    if (has_else_branch) {
        const_point_watcher *else_watcher = materials->else_watcher;
        new_point = else_watcher->end - 1;
        //Create else holder:
        new_else_holder
                = inflate_local_aio_instruction_holder(source_code, parent, else_watcher->start, else_watcher->end);
    } else {
        new_point = body_watcher->end - 1;
    }
    const_string dirty_switch_value = substring_by_point_watcher(source_code, header_watcher);
    const_string new_switch_value = squeeze_string(dirty_switch_value);
    //Set new start point for ripper:
    ripper_watcher->pointer = new_point;
    ripper_watcher->start = new_point;
    //Create instruction:
    aio_function_instruction *instruction = new_aio_switch_instruction(parent, new_switch_value, new_case_key_list,
                                                                       new_case_holders, new_else_holder);
    //명부에게 지침을 추가하다 (Add 'Switch' instruction in holder's instructions):
    aio_function_instruction_list *instruction_list = holder->instruction_list;
    add_aio_instruction_in_list(instruction_list, instruction);
    //위빙이 완료되었습니다 (Weaving complete)!
#ifdef AIO_SWITCH_SPIDER_DEBUG
    log_info(AIO_SWITCH_SPIDER_TAG, "WEAVED INSTRUCTION:");
    const aio_switch_task *task = instruction->get.switch_task;
    log_info_string(AIO_SWITCH_SPIDER_TAG, "<SWITCH VALUE>:", task->switch_value);
    string_list *case_keys = task->case_keys;
    for (int j = 0; j < case_keys->size; ++j) {
        log_info_string(AIO_SWITCH_SPIDER_TAG, "<CASE KEY>:", case_keys->strings[j]);
    }
#endif
    //------------------------------------------------------------------------------------------------------------------
    //찌거기 수집기 (Garbage collector):
    free((void *) dirty_switch_value);
}

string_list *extract_case_keys_from_hook(const_str_hook *case_keys_hook) {
    static const_string OPENING_PARENTHESIS = "(";
    static const_string CLOSING_PARENTHESIS = ")";
    string_list *case_key_list = new_string_list();
    //Extract string from hook:
    const_string dirty_case_key_chunk = substring_by_str_hook(case_keys_hook);
    string case_key_chunk = squeeze_string(dirty_case_key_chunk);
    const_boolean is_many_cases = starts_with_prefix(case_key_chunk, OPENING_PARENTHESIS)
                                  || ends_with_suffix(case_key_chunk, CLOSING_PARENTHESIS);
    if (is_many_cases) {
        const_string naked_case_chunk = remove_prefix_suffix(case_key_chunk, OPENING_PARENTHESIS, CLOSING_PARENTHESIS);
        const_string_array case_key_array = split_by_comma(naked_case_chunk);
        const int case_key_array_size = get_string_array_size(case_key_array);
        for (int i = 0; i < case_key_array_size; ++i) {
            add_string_in_list(case_key_list, case_key_array[i]);
        }
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free(case_key_chunk);
        free((void *) naked_case_chunk);
        free(case_key_array);
    } else {
        add_string_in_list(case_key_list, case_key_chunk);
    }
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free((void *) dirty_case_key_chunk);
    return case_key_list;
}