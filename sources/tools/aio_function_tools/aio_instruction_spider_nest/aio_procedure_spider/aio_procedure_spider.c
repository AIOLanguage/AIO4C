#include <malloc.h>
#include <ctype.h>
#include "../../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"
#include "../../../../../headers/tools/aio_common_tools/aio_spider_nest/aio_spider.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instruction_spider_nest/aio_procedure_spider/aio_procedure_spider.h"
#include "../../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"
#include "../../../../../headers/tools/aio_common_tools/aio_block_body_explorer/aio_block_body_explorer.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_function_instruction.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_procedure_task.h"

#define AIO_PROCEDURE_SPIDER_DEBUG

#define AIO_PROCEDURE_SPIDER_TAG "AIO_PROCEDURE_SPIDER"

#ifdef AIO_PROCEDURE_SPIDER_DEBUG

#include "../../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

/**
 * Refresh.
 */

void refresh_procedure_spider(aio_spider *spider, point_watcher *ripper_watcher) {
    aio_procedure_materials *materials = spider->materials;
    materials->scope_type = AIO_PROCEDURE_NAME_SCOPE;
    point_watcher *main_watcher = materials->main_watcher;
    main_watcher->start = ripper_watcher->pointer;
    main_watcher->end = ripper_watcher->pointer;
    main_watcher->mode = POINT_WATCHER_PASSIVE_MODE;
//#ifdef AIO_PROCEDURE_SPIDER_DEBUG
//    log_info(AIO_PROCEDURE_SPIDER_TAG, "Refresh is complete!");
//#endif
}

/**
 * Free spider.
 */

void free_procedure_spider(aio_spider *spider) {
    aio_procedure_materials *materials = spider->materials;
    point_watcher *watcher = materials->main_watcher;
    free_point_watcher(watcher);
    free(materials);
    free(spider);
}

struct aio_spider *new_aio_procedure_spider(point_watcher *ripper_watcher) {
    aio_spider *spider = new_object(sizeof(aio_spider));
    //Bind main spider's functions:
    spider->refresh = refresh_procedure_spider;
    spider->is_found_context = is_found_procedure_instruction;
    spider->weave_context_for = weave_procedure_instruction_for;
    spider->free = free_procedure_spider;
    //Create materials:
    aio_procedure_materials *materials = new_object(sizeof(aio_procedure_materials));
    materials->scope_type = AIO_PROCEDURE_NAME_SCOPE;
    materials->main_watcher = new_point_watcher();
    materials->main_watcher->start = ripper_watcher->start;
    materials->main_watcher->end = ripper_watcher->pointer;
    spider->materials = materials;
    //Init start message:
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    return spider;
}

const enum aio_spider_message is_found_procedure_instruction(const_string source_code, point_watcher *ripper_watcher,
                                                             struct aio_spider *spider) {
    const aio_procedure_materials *materials = spider->materials;
    point_watcher *watcher = materials->main_watcher;
    watcher->end = ripper_watcher->pointer;
    const char current_symbol = source_code[watcher->end];
    //FIXME: Code duplication!
    if (watcher->mode == POINT_WATCHER_PASSIVE_MODE) {
        if (is_space_or_line_break(current_symbol)) {
            watcher->start++;
        } else {
            watcher->mode = POINT_WATCHER_ACTIVE_MODE;
        }
    }
    if (watcher->mode == POINT_WATCHER_ACTIVE_MODE) {
        if (materials->scope_type == AIO_PROCEDURE_NAME_SCOPE) {
            handle_procedure_name_scope(source_code, spider);
        }
        if (materials->scope_type == AIO_PROCEDURE_ARG_SCOPE) {
            handle_procedure_arg_scope(source_code, spider);
        }
    }
    return spider->message;
}

void handle_procedure_name_scope(const_string source_code, aio_spider *spider) {
    //재료들을 추출하다 (Extract materials):
    aio_procedure_materials *materials = spider->materials;
    point_watcher *main_watcher = materials->main_watcher;
    //Define current symbol:
    const int current_position = main_watcher->end;
    const char current_symbol = source_code[current_position];
    //Check current symbol:
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    const_boolean is_opening_parenthesis_cond = is_opening_parenthesis(current_symbol);
    if (is_whitespace_cond || is_opening_parenthesis_cond) {
        const_str_hook *hook = new_str_hook_by_point_watcher(source_code, main_watcher);
#ifdef AIO_PROCEDURE_SPIDER_DEBUG
        log_info_str_hook(AIO_PROCEDURE_SPIDER_TAG, "CAPTURED NAME:", hook);
#endif
        const_boolean is_function_name = is_word_hooked(hook) && can_use_name(hook);
        if (is_function_name) {
            main_watcher->mode = POINT_WATCHER_PASSIVE_MODE;
            materials->scope_type = AIO_PROCEDURE_ARG_SCOPE;
        }
    }
}

void handle_procedure_arg_scope(const_string source_code, aio_spider *spider) {
    aio_procedure_materials *materials = spider->materials;
    point_watcher *main_watcher = materials->main_watcher;
    //Define current symbol:
    const int current_position = main_watcher->end;
    const char current_symbol = source_code[current_position];
    //Check current symbol:
    if (is_space_or_line_break(current_symbol)) {
        return;
    }
    if (is_opening_parenthesis(current_symbol)) {
#ifdef AIO_PROCEDURE_SPIDER_DEBUG
        log_info(AIO_PROCEDURE_SPIDER_TAG, "Found opening parenthesis!");
#endif
        int start_index = current_position;
        int end_index = 0;
        explore_aio_header_bounds(source_code, &start_index, &end_index);
        main_watcher->end = end_index;
        materials->scope_type = AIO_PROCEDURE_WEAVING_SCOPE;
        spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
    }
}

void weave_procedure_instruction_for(void *parent, const_string source_code,
                                     point_watcher *ripper_watcher, struct aio_spider *spider) {
    aio_function_instruction_holder *holder = parent;
#ifdef AIO_PROCEDURE_SPIDER_DEBUG
    log_info(AIO_PROCEDURE_SPIDER_TAG, "Start weaving...");
#endif
    //재료들을 추출하다 (Extract materials):
    const aio_procedure_materials *materials = spider->materials;
    const point_watcher *watcher = materials->main_watcher;
    //Change ripper_watcher:
    const int new_point = watcher->end;
    ripper_watcher->pointer = new_point;
    ripper_watcher->start = new_point;
    string dirty_expression = substring_by_point_watcher(source_code, watcher);
    string clean_expression = squeeze_string_for_expression(dirty_expression);
#ifdef AIO_PROCEDURE_SPIDER_DEBUG
    log_info_string(AIO_PROCEDURE_SPIDER_TAG, "CAPTURED EXPRESSION:", clean_expression);
#endif
    aio_function_instruction *instruction = new_aio_procedure_instruction(parent, clean_expression);
    //명부에게 지침을 추가하다 (Add 'Procedure' instruction in holder's instructions):
    aio_function_instruction_list *instruction_list = holder->instruction_list;
    add_aio_instruction_in_list(instruction_list, instruction);
    //위빙이 완료되었습니다 (Weaving complete)!
#ifdef AIO_PROCEDURE_SPIDER_DEBUG
    log_info(AIO_PROCEDURE_SPIDER_TAG, "WEAVED INSTRUCTION:");
    log_info_string(AIO_PROCEDURE_SPIDER_TAG, "EXPRESSION:", instruction->get.procedure_task->procedure);
#endif
    //------------------------------------------------------------------------------------------------------------------
    //찌거기 수집기 (Garbage collector):
    free(dirty_expression);
}