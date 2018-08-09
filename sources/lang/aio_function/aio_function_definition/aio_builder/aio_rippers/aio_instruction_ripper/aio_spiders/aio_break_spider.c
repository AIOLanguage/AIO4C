#include <malloc.h>
#include <mem.h>
#include "../../../../../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_spider/aio_spiders.h"
#include "../../../../../../../../headers/lib/point_watcher/point_watcher.h"
#include "../../../../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../../../../headers/lib/utils/error_utils/error_utils.h"

/**
 * Declare functions. 
 */

const enum aio_spider_message is_found_break_instruction(const_string string_web, aio_spider *spider);

void weave_break_instruction_for(aio_instruction_holder *instruction_holder, int *next_ripper_point_reference,
                                 struct aio_spider *spider);

void free_break_function(struct aio_spider *spider);

void reset_break_spider(struct aio_spider *spider);

aio_spider *new_aio_break_spider() {
    aio_spider *spider = calloc(1, sizeof(aio_spider));
    //Bind main spider's functions:
    spider->reset = reset_break_spider;
    spider->is_found_instruction = is_found_break_instruction;
    spider->weave_instruction_for = weave_break_instruction_for;
    spider->free = free_break_function;
    //Init start scanning position:
    spider->start_pointer = 0;
    return spider;
}

const enum aio_spider_message is_found_break_instruction(const_string string_web, aio_spider *spider) {
    //If pointer doesn't equal zero then spider found something:
    const_boolean is_ready = spider->start_pointer != 0;
    if (is_ready) {
        return AIO_SPIDER_IS_READY_FOR_WEAVING;
    } else {
        const size_t string_web_length = strlen(string_web);
        point_watcher *watcher = new_point_watcher();
        for (int i = 0; i < string_web_length; ++i) {
            const char symbol = string_web[i];
            const_boolean is_whitespace_or_line_break = !is_space_or_line_break(symbol);
            if (watcher->mode == POINT_PASSIVE_MODE && is_whitespace_or_line_break) {
                watcher->mode = POINT_ACTIVE_MODE;
                watcher->start_index = i;
            }
            if (watcher->mode == POINT_ACTIVE_MODE && is_whitespace_or_line_break) {
                watcher->end_index = i;
                break;
            }
        }
        const int start_index = watcher->start_index;
        const int end_index = watcher->end_index;
        const int captured_length = end_index - start_index;
        if (captured_length == 3) {
            const_boolean is_break_word = string_web[start_index] == 'b'
                                          && string_web[start_index + 1] == 'r'
                                          && string_web[start_index + 2] == 'k';
            if (is_break_word) {
                spider->start_pointer = end_index;
                return AIO_SPIDER_FOUND_MATERIALS;
            }
        } else {
            return AIO_SPIDER_NOT_FOUND_MATERIALS;
        }
    }
}

void weave_break_instruction_for(aio_instruction_holder *instruction_holder, int *next_ripper_point_reference,
                                 struct aio_spider *spider) {
    //If pointer doesn't equal zero then spider found something:
    const_boolean is_ready_for_weaving = spider->start_pointer != 0;
    if (is_ready_for_weaving) {
        *next_ripper_point_reference += spider->start_pointer;
        //Weave break instruction:
        aio_instruction *break_instruction = new_aio_break_instruction(instruction_holder);
        //Add break instruction in holder's instructions:
        aio_instruction_list *instruction_list = instruction_holder->instruction_list;
        add_aio_instruction_in_list(instruction_list, break_instruction);
        //Weaving complete!
    } else {
        throw_error("ASSIGN SPIDER: not ready for weaving!");
    }
}

void reset_break_spider(struct aio_spider *spider) {
    spider->start_pointer = 0;
}

void free_break_function(struct aio_spider *spider) {
    free(spider);
}