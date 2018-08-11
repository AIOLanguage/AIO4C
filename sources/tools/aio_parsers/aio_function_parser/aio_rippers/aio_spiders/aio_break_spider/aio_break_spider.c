#include <malloc.h>
#include <mem.h>
#include "../../../../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../../../headers/lib/point_watcher/point_watcher.h"
#include "../../../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../../../headers/tools/aio_parsers/aio_function_parser/aio_rippers/aio_spiders/aio_spider.h"

/**
 * Declare functions. 
 */

const aio_spider_message is_found_break_instruction(const_string string_web, aio_spider *spider);

void weave_break_instruction_for(aio_instruction_holder *instruction_holder, const_string _,
                                 int *next_ripper_point_reference, aio_spider *spider);

void handle_break_scope(const_string string_web, aio_spider *spider);

/**
 * Reset.
 */

void reset_break_spider(aio_spider *spider) {
    reset_point_watcher(spider->get.break_materials->watcher);
}

/**
 * Destructor.
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

aio_spider *new_aio_break_spider() {
    aio_spider *spider = calloc(1, sizeof(aio_spider));
    //Bind main spider's functions:
    spider->reset = reset_break_spider;
    spider->is_found_instruction = is_found_break_instruction;
    spider->weave_instruction_for = weave_break_instruction_for;
    spider->free = free_break_function;
    //Create materials:
    aio_break_materials *materials = calloc(1, sizeof(aio_break_materials));
    materials->watcher = new_point_watcher();
    spider->get.break_materials = materials;
    //Init start message:
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    return spider;
}

const aio_spider_message is_found_break_instruction(const_string string_web, aio_spider *spider) {
    //Extract spider fields:
    const aio_break_materials *materials = spider->get.break_materials;
    point_watcher *watcher = materials->watcher;
    watcher->end_index++;
    //Prepare from scanning:
    const char last_symbol = string_web[watcher->end_index - 1];
    //Spider waits string data:
    if (watcher->mode == POINT_PASSIVE_MODE) {
        if (is_space_or_line_break(last_symbol)) {
            //Spider waiting:
            watcher->start_index++;
        } else {
            //Spider is ready for analysing:
            watcher->mode = POINT_ACTIVE_MODE;
        }
    }
    //Spider works:
    if (watcher->mode == POINT_ACTIVE_MODE) {
        handle_break_scope(string_web, spider);
    }
    return spider->message;
}

void handle_break_scope(const_string string_web, aio_spider *spider) {
    const aio_break_materials *materials = spider->get.break_materials;
    point_watcher *watcher = materials->watcher;
    const char last_symbol = string_web[watcher->end_index - 1];
    if (is_space_or_line_break(last_symbol)) {
        const int start_index = watcher->start_index;
        const int end_index = watcher->end_index;
        const int hold_positions = end_index - start_index;
        if (hold_positions == 3) {
            const_boolean is_break_word = string_web[start_index] == 'b'
                                          && string_web[start_index + 1] == 'r'
                                          && string_web[start_index + 2] == 'k';
            if (is_break_word) {
                //Shift main_watcher:
                watcher->start_index = end_index;
                watcher->mode = POINT_PASSIVE_MODE;
                //Set message:
                spider->message = AIO_SPIDER_FOUND_MATERIALS;
            }
        }
    }
}

void weave_break_instruction_for(aio_instruction_holder *instruction_holder, const_string _,
                                 int *next_ripper_point_reference, aio_spider *spider) {
    *next_ripper_point_reference += spider->get.break_materials->watcher->start_index;
    //Weave break instruction:
    aio_instruction *break_instruction = new_aio_break_instruction(instruction_holder);
    //Add break instruction in holder's instructions:
    aio_instruction_list *instruction_list = instruction_holder->instruction_list;
    add_aio_instruction_in_list(instruction_list, break_instruction);
    //Weaving complete!
}