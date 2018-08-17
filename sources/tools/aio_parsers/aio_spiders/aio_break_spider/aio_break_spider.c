#include <malloc.h>
#include <mem.h>
#include "../../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../headers/lib/point_watcher/point_watcher.h"
#include "../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../headers/tools/aio_parsers/aio_spiders/aio_spider.h"
#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"

#define AIO_BREAK_SPIDER_DEBUG

#define AIO_BREAK_SPIDER_TAG "AIO_BREAK_SPIDER"

#ifdef AIO_BREAK_SPIDER_DEBUG

#include "../../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

/**
 * Refresh.
 */

void refresh_break_spider(aio_spider *spider, point_watcher *ripper_watcher) {
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    point_watcher *main_watcher = spider->get.break_materials->watcher;
    main_watcher->start = ripper_watcher->pointer;
    main_watcher->end = ripper_watcher->pointer;
    main_watcher->mode = POINT_PASSIVE_MODE;
}

/**
 * Free spider.
 */

void free_break_function(aio_spider *spider) {
    aio_break_materials *materials = spider->get.break_materials;
    point_watcher *watcher = materials->watcher;
    free_point_watcher(watcher);
    free(materials);
    free(spider);
}

/**
 * Constructor.
 */

struct aio_spider *new_aio_break_spider(point_watcher *ripper_watcher) {
    aio_spider *spider = new_object(sizeof(aio_spider));
    //Bind main spider's functions:
    spider->refresh = refresh_break_spider;
    spider->is_found_instruction = is_found_break_instruction;
    spider->weave_instruction_for = weave_break_instruction_for;
    spider->free = free_break_function;
    //Create materials:
    aio_break_materials *materials = new_object(sizeof(aio_break_materials));
    materials->watcher = new_point_watcher();
    materials->watcher->start = ripper_watcher->start;
    materials->watcher->end = ripper_watcher->pointer;
    spider->get.break_materials = materials;
    //Init start message:
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    return spider;
}

const aio_spider_message is_found_break_instruction(const_string source_code, point_watcher *ripper_watcher,
                                                    aio_spider *spider) {
    const aio_break_materials *materials = spider->get.break_materials;
    point_watcher *watcher = materials->watcher;
    watcher->end = ripper_watcher->pointer;
    const char current_symbol = source_code[watcher->end];
    if (watcher->mode == POINT_PASSIVE_MODE) {
        if (is_space_or_line_break(current_symbol)) {
            watcher->start++;
        } else {
            watcher->mode = POINT_ACTIVE_MODE;
        }
    }
    if (watcher->mode == POINT_ACTIVE_MODE) {
        handle_break_scope(source_code, spider);
    }
    return spider->message;
}

void handle_break_scope(const_string source_code, aio_spider *spider) {
    const aio_break_materials *materials = spider->get.break_materials;
    point_watcher *watcher = materials->watcher;
    const char current_symbol = source_code[watcher->end];
    if (is_space_or_line_break(current_symbol) || is_closing_brace(current_symbol)) {
        const int start_index = watcher->start;
        const int end_index = watcher->end;
        const int hold_positions = end_index - start_index;
        if (hold_positions == 3) {
            const_boolean is_break_word = source_code[start_index] == 'b'
                                          && source_code[start_index + 1] == 'r'
                                          && source_code[start_index + 2] == 'k';
            if (is_break_word) {
                //Shift main_watcher:
                watcher->start = end_index;
                watcher->mode = POINT_PASSIVE_MODE;
                //Set message:
                spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
#ifdef AIO_BREAK_SPIDER_DEBUG
                log_info(AIO_BREAK_SPIDER_TAG, "Found break modifier");
#endif
            }
        }
    }
}

void weave_break_instruction_for(aio_instruction_holder *instruction_holder, const_string _,
                                 point_watcher *ripper_watcher, aio_spider *spider) {
#ifdef AIO_BREAK_SPIDER_DEBUG
    log_info(AIO_BREAK_SPIDER_TAG, "Start weaving...");
#endif
    const int start_index = spider->get.break_materials->watcher->start;
    ripper_watcher->start = start_index;
    ripper_watcher->pointer = start_index;
    //Weave break instruction:
    aio_instruction *break_instruction = new_aio_break_instruction(instruction_holder);
    //Add break instruction in holder's instructions:
    aio_instruction_list *instruction_list = instruction_holder->instruction_list;
    add_aio_instruction_in_list(instruction_list, break_instruction);
    //Weaving is complete!
#ifdef AIO_BREAK_SPIDER_DEBUG
    log_info(AIO_BREAK_SPIDER_TAG, "Weaving is complete!");
#endif
}