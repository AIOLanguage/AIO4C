#include <malloc.h>
#include "../../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../headers/lib/point_watcher/point_watcher.h"
#include "../../../../../headers/tools/aio_parsers/aio_spiders/aio_spider.h"
#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../headers/lib/utils/log_utils/log_utils.h"

#define AIO_RETURN_SPIDER_DEBUG

#define AIO_RETURN_SPIDER_TAG "AIO_RETURN_SPIDER"

#ifdef AIO_RETURN_SPIDER_DEBUG


#endif

/**
 * Refresh.
 */

void refresh_return_spider(aio_spider *spider, point_watcher *ripper_watcher) {
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    //재료 리셋 (Reset materials):
    aio_return_materials *materials = spider->get.return_materials;
    point_watcher *main_watcher = materials->main_watcher;
    main_watcher->start_index = ripper_watcher->pointer;
    main_watcher->end_index = ripper_watcher->pointer;
    main_watcher->mode = POINT_PASSIVE_MODE;
    reset_point_watcher(materials->value_watcher);
    materials->scope_type = AIO_RETURN_MODIFIER_SCOPE;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    string_list *old_return_values = materials->value_list;
    free_strings_in_list(old_return_values);
    free_string_list(old_return_values);
    //------------------------------------------------------------------------------------------------------------------
    materials->value_list = new_string_list();
}

/**
 * 거미를 비우다 (Free spider).
 */

void free_return_spider(aio_spider *spider) {
    aio_return_materials *materials = spider->get.return_materials;
    free_point_watcher(materials->main_watcher);
    free_point_watcher(materials->value_watcher);
    free_strings_in_list(materials->value_list);
    free_string_list(materials->value_list);
    free(materials);
    free(spider);
}

/**
 * 건설자 (Constructor).
 */

struct aio_spider *new_aio_return_spider(point_watcher *ripper_watcher) {
    aio_spider *spider = new_object(sizeof(aio_spider));
    //함수들을 놓다 (Put functions):
    spider->refresh = refresh_return_spider;
    spider->is_found_instruction = is_found_return_instruction;
    spider->weave_instruction_for = weave_return_instruction_for;
    spider->free = free_return_spider;
    //재료들을 만들다 (Create materials):
    aio_return_materials *materials = new_object(sizeof(aio_return_materials));
    materials->scope_type = AIO_RETURN_MODIFIER_SCOPE;
    materials->main_watcher = new_point_watcher();
    materials->main_watcher->start_index = ripper_watcher->start_index;
    materials->main_watcher->end_index = ripper_watcher->pointer;
    materials->value_watcher = new_point_watcher();
    materials->value_list = new_string_list();
    //재료들을 놀다 (Set materials):
    spider->get.return_materials = materials;
    //시작 메시지 초기화하다 (Init start message):
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    return spider;
}

const enum aio_spider_message is_found_return_instruction(const_string source_code, point_watcher *ripper_watcher,
                                                          struct aio_spider *spider) {
    //재료들을 추출하다 (Extract materials):
    const aio_return_materials *materials = spider->get.return_materials;
    point_watcher *main_watcher = materials->main_watcher;
    main_watcher->end_index = ripper_watcher->pointer;
    //Define current symbol:
    const char current_symbol = source_code[main_watcher->end_index];
    //TODO: 코드 복제 (Code duplication)!
    if (main_watcher->mode == POINT_PASSIVE_MODE) {
        if (is_space_or_line_break(current_symbol)) {
            main_watcher->start_index++;
        } else {
            main_watcher->mode = POINT_ACTIVE_MODE;
        }
    }
    if (main_watcher->mode == POINT_ACTIVE_MODE) {
        if (materials->scope_type == AIO_RETURN_MODIFIER_SCOPE) {
            handle_return_modifier_scope(source_code, spider);
        }
        if (materials->scope_type == AIO_RETURN_VALUE_SCOPE) {
            handle_return_value_scope(source_code, spider);
        }
    }
    return spider->message;
}

void handle_return_modifier_scope(const_string source_code, struct aio_spider *spider) {
    aio_return_materials *materials = spider->get.return_materials;
    point_watcher *main_watcher = materials->main_watcher;
    const int current_position = main_watcher->end_index;
    const char current_symbol = source_code[current_position];
    //Check current symbol:
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    if (is_whitespace_cond) {
        const int start_index = main_watcher->start_index;
        const int hold_positions = current_position - start_index;
        if (hold_positions == 3) {
            const_boolean is_return_modifier =
                    source_code[start_index] == 'o'
                    && source_code[start_index + 1] == 'u'
                    && source_code[start_index + 2] == 't';
            if (is_return_modifier) {
                //Shift main_watcher:
                main_watcher->start_index = current_position;
                main_watcher->mode = POINT_PASSIVE_MODE;
                //Set scope:
                materials->scope_type = AIO_RETURN_VALUE_SCOPE;
                //Set message:
                spider->message = AIO_SPIDER_FOUND_MATERIALS;
#ifdef AIO_RETURN_SPIDER_DEBUG
                log_info(AIO_RETURN_SPIDER_TAG, "Found return modifier!");
#endif
            }
        }
    }
}

void handle_return_value_scope(const_string source_code, struct aio_spider *spider) {

}

void weave_return_instruction_for(aio_instruction_holder *holder, const_string _,
                                  point_watcher *ripper_watcher, struct aio_spider *spider) {

}