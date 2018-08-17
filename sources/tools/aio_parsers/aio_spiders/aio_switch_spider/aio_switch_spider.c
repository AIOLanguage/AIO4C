#include "../../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../headers/tools/aio_parsers/aio_spiders/aio_spider.h"


#define AIO_PROCEDURE_SPIDER_DEBUG

#define AIO_PROCEDURE_SPIDER_TAG "AIO_PROCEDURE_SPIDER"

#ifdef AIO_PROCEDURE_SPIDER_DEBUG

#include "../../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

/**
 * Refresh.
 */

void refresh_switch_spider(aio_spider *spider, point_watcher *ripper_watcher) {
//    aio_procedure_materials *materials = spider->get.procedure_materials;
//    materials->scope_type = AIO_PROCEDURE_NAME_SCOPE;
//    point_watcher *main_watcher = materials->main_watcher;
//    main_watcher->start = ripper_watcher->pointer;
//    main_watcher->end_ = ripper_watcher->pointer;
//    main_watcher->mode = POINT_PASSIVE_MODE;
}

/**
 * Free spider.
 */

void free_switch_function(aio_spider *spider) {
//    aio_procedure_materials *materials = spider->get.procedure_materials;
//    point_watcher *watcher = materials->main_watcher;
//    free_point_watcher(watcher);
//    free(materials);
//    free(spider);
}

struct aio_spider *new_aio_switch_spider(point_watcher *ripper_watcher) {
//    aio_spider *spider = new_object(sizeof(aio_spider));
//    //Bind main spider's functions:
//    spider->refresh = refresh_procedure_spider;
//    spider->is_found_instruction = is_found_procedure_instruction;
//    spider->weave_instruction_for = weave_procedure_instruction_for;
//    spider->free = free_procedure_function;
//    //Create materials:
//    aio_procedure_materials *materials = new_object(sizeof(aio_procedure_materials));
//    materials->scope_type = AIO_PROCEDURE_NAME_SCOPE;
//    materials->main_watcher = new_point_watcher();
//    materials->main_watcher->start = ripper_watcher->start;
//    materials->main_watcher->end_ = ripper_watcher->pointer;
//    spider->get.procedure_materials = materials;
//    //Init start message:
//    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
//    return spider;
}

const enum aio_spider_message is_found_switch_instruction(const_string source_code, point_watcher *ripper_watcher,
                                                             struct aio_spider *spider) {
//    const aio_procedure_materials *materials = spider->get.procedure_materials;
//    point_watcher *watcher = materials->main_watcher;
//    watcher->end_ = ripper_watcher->pointer;
//    const char current_symbol = source_code[watcher->end_];
//    if (watcher->mode == POINT_PASSIVE_MODE) {
//        if (is_space_or_line_break(current_symbol)) {
//            watcher->start++;
//        } else {
//            watcher->mode = POINT_ACTIVE_MODE;
//        }
//    }
//    if (watcher->mode == POINT_ACTIVE_MODE) {
//        if (materials->scope_type == AIO_PROCEDURE_NAME_SCOPE) {
//            handle_procedure_name_scope(source_code, spider);
//        }
//        if (materials->scope_type == AIO_PROCEDURE_ARG_SCOPE) {
//            handle_procedure_arg_scope(source_code, spider);
//        }
//    }
//    return spider->message;
}

void handle_switch_name_scope(const_string source_code, aio_spider *spider) {
//    //재료들을 추출하다 (Extract materials):
//    aio_procedure_materials *materials = spider->get.procedure_materials;
//    point_watcher *main_watcher = materials->main_watcher;
//    //Define current symbol:
//    const int current_position = main_watcher->end_;
//    const char current_symbol = source_code[current_position];
//    //Check current symbol:
//    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
//    const_boolean is_opening_parenthesis_cond = is_opening_parenthesis(current_symbol);
//    if (is_whitespace_cond || is_opening_parenthesis_cond) {
//        const_string chunk = substring_by_point_watcher(source_code, main_watcher);
//#ifdef AIO_PROCEDURE_SPIDER_DEBUG
//        log_info_string(AIO_PROCEDURE_SPIDER_TAG, "CAPTURED NAME:", chunk);
//#endif
//        const_boolean is_function_name = is_word(chunk) && can_use_name(chunk);
//        if (is_function_name) {
//            main_watcher->mode = POINT_PASSIVE_MODE;
//            materials->scope_type = AIO_PROCEDURE_ARG_SCOPE;
//        }
//    }
}