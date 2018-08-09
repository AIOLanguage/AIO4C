#include <malloc.h>
#include <mem.h>
#include "../../../../../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_spider/aio_spiders.h"
#include "../../../../../../../../headers/lib/point_watcher/point_watcher.h"
#include "../../../../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../../../../headers/lib/utils/string_utils/string_builder.h"
#include "../../../../../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"

//----------------------------------------------------------------------------------------------------------------------
//PROTOCOL:

#define AIO_NUMBER_OF_PROTOCOL_CELLS 6

/**
 * Scopes.
 */

#define AIO_SCOPE_INDEX 0

const int AIO_IF_SCOPE = 0;

const int AIO_CONDITION_SCOPE = 1;

const int AIO_TRUE_BODY_SCOPE = 2;

const int AIO_ELSE_SCOPE = 3;

const int AIO_FALSE_BODY_SCOPE = 4;

/**
 * Branches.
 */

#define AIO_BRANCHES_INDEX 1

const int AIO_UNDEFINED_BRANCHES = 0;

const int AIO_HAS_TRUE_BRANCH = 1;

const int AIO_HAS_TRUE_AND_FALSE_BRANCHES = 2;

/**
 * Start & end true & false branch index.
 */

#define AIO_START_TRUE_POSITION_INDEX 2

#define AIO_END_TRUE_POSITION_INDEX 3

#define AIO_START_FALSE_POSITION_INDEX 4

#define AIO_END_FALSE_POSITION_INDEX 5

//----------------------------------------------------------------------------------------------------------------------
//MATERIALS:

#define AIO_NUMBER_OF_MATERIALS 2

const int AIO_IF_CONDITION_INDEX = 0;

//----------------------------------------------------------------------------------------------------------------------

/**
 * Declare functions.
 */

void reset_if_spider(struct aio_spider *spider);

const enum aio_spider_message is_found_if_instruction(const_string string_web, aio_spider *spider);

void weave_if_instruction_for(aio_instruction_holder *instruction_holder, int *next_ripper_point_reference,
                              struct aio_spider *spider);

void free_if_spider(struct aio_spider *spider);

const_boolean handle_if_scope(string chunk, const int position, int *spider_protocol, int *spider_pointer_reference);

const_boolean handle_condition_scope(string chunk, const int position, int *spider_protocol,
                                     int *spider_pointer_reference,
                                     aio_spider_materials materials);

const_boolean handle_else_scope(string chunk, const int position, int *spider_protocol, int *spider_pointer_reference);

/**
 * Constructor.
 */

aio_spider *new_aio_if_spider() {
    aio_spider *spider = calloc(1, sizeof(aio_spider));
    //Bind main spider's functions:
    spider->reset = reset_if_spider;
    spider->is_found_instruction = is_found_if_instruction;
    spider->weave_instruction_for = weave_if_instruction_for;
    spider->free = free_if_spider;
    //Init start scanning position:
    spider->start_pointer = 0;
    //Create spider's protocol:
    spider->spider_protocol = calloc(AIO_NUMBER_OF_PROTOCOL_CELLS, sizeof(int));
    //Create spider materials:
    spider->collected_materials = new_aio_spider_materials(AIO_NUMBER_OF_MATERIALS);
    return spider;
}

/**
 * Reset.
 */

void reset_if_spider(struct aio_spider *spider) {
    spider->start_pointer = 0;
    //Reset protocol:
    int *protocol = spider->spider_protocol;
    protocol[AIO_SCOPE_INDEX] = AIO_IF_SCOPE;
    protocol[AIO_BRANCHES_INDEX] = AIO_UNDEFINED_BRANCHES;
    protocol[AIO_START_TRUE_POSITION_INDEX] = -1;
    protocol[AIO_END_TRUE_POSITION_INDEX] = -1;
    protocol[AIO_START_FALSE_POSITION_INDEX] = -1;
    protocol[AIO_END_FALSE_POSITION_INDEX] = -1;
    reset_aio_spider_materials(spider->collected_materials, AIO_NUMBER_OF_MATERIALS);
}

/**
 * Destructor.
 */

void free_if_spider(struct aio_spider *spider) {
    free(spider->spider_protocol);
    for (int i = 0; i < AIO_NUMBER_OF_MATERIALS; ++i) {
        string_list *material_list = spider->collected_materials[i];
        free_string_list(material_list);
    }
    free(spider);
}

/**
 * Searching.
 */

const enum aio_spider_message is_found_if_instruction(const_string string_web, aio_spider *spider) {
    //Extract spider fields:
    int *start_point_reference = &spider->start_pointer;
    int *spider_protocol = spider->spider_protocol;
    aio_spider_materials materials = spider->collected_materials;
    //Extract protocol:
    const int scanning_scope = spider_protocol[AIO_SCOPE_INDEX];
    const_boolean is_modifier_scanning_mode = scanning_scope == AIO_IF_SCOPE || scanning_scope == AIO_ELSE_SCOPE;
    //Prepare to scanning:
    const int start_point = *start_point_reference;
    const size_t string_web_length = strlen(string_web);
    point_watcher *watcher = new_point_watcher();
    //Scan string web:
    for (int i = start_point; i < string_web_length; ++i) {
        const char symbol = string_web[i];
        const_boolean is_space_or_line_break_condition = is_space_or_line_break(symbol);
        //Start read word:
        if (!is_space_or_line_break_condition && watcher->mode == POINT_PASSIVE_MODE) {
            if (is_modifier_scanning_mode) {
                watcher->mode = POINT_ACTIVE_MODE;
                watcher->start_index = i;
            } else {
                watcher->mode = POINT_UNDEFINED_MODE;
            }
        }
        //End read word:
        if (is_space_or_line_break_condition && watcher->mode == POINT_ACTIVE_MODE) {
            //Turn off watcher:
            watcher->mode = POINT_PASSIVE_MODE;
            watcher->end_index = i;
            //Extract first string:
            string chunk = substring(string_web, watcher->start_index, watcher->end_index);
            //Watching scopes:
            switch (spider_protocol[AIO_SCOPE_INDEX]) {
                //------------------------------------------------------------------------------------------------------
                //If scope:
                case 0: {
                    const_boolean is_changed_state = handle_if_scope(chunk, i, spider_protocol, start_point_reference);
                    if (is_changed_state) {
                        return AIO_SPIDER_FOUND_MATERIALS;
                    }
                }
                    break;
                    //--------------------------------------------------------------------------------------------------
                    //Else scope:
                case 3:
                    handle_else_scope(chunk, i, spider_protocol, start_point_reference);
                    break;
                default:
                    break;
            }
            return AIO_SPIDER_NOT_FOUND_MATERIALS;
        }
        //Scan condition, true & false function bodies:
        if (watcher->mode == POINT_UNDEFINED_MODE && !is_modifier_scanning_mode) {
            //Extract necessary part of string web:
            string chunk = substring(string_web, start_point, string_web_length);
            switch (scanning_scope) {
                //Condition scope:
                case 1:
                    handle_condition_scope(chunk, i, spider_protocol, start_point_reference, materials);
                    break;
                    //True body scope;
                case 2:
                    handle_true_body(chunk, i, spider_protocol, start_point_reference, materials);
                    break;
                    //False body scope
                case 4:
                    handle_false_body(chunk, i, spider_protocol, start_point_reference, materials);
                    break;
                    //Unreachable case:
                default:
                    break;
            }
        }
    }
    return AIO_SPIDER_NOT_FOUND_MATERIALS;
}


const_boolean handle_if_scope(string chunk, const int position, int *spider_protocol, int *spider_pointer_reference) {
    const_boolean is_if_modifier = is_aio_if_modifier(chunk);
    if (is_if_modifier) {
        spider_protocol[AIO_SCOPE_INDEX] = AIO_CONDITION_SCOPE;
        *spider_pointer_reference = position;
    }
    return is_if_modifier;
}

const_boolean handle_else_scope(string chunk, const int position, int *spider_protocol, int *spider_pointer_reference) {
    const_boolean is_colon_condition = is_colon(chunk[0]);
    if (is_colon_condition) {
        spider_protocol[AIO_SCOPE_INDEX] = AIO_FALSE_BODY_SCOPE;
        *spider_pointer_reference = position;
    }
    return is_colon_condition;
}

const_boolean handle_condition_scope(string chunk, const int position, int *spider_protocol,
                                     int *spider_pointer_reference,
                                     aio_spider_materials materials) {
    const size_t chunk_length = strlen(chunk);
    const int last_position = chunk_length - 1;
    if (chunk_length >= 3) {
        const_boolean starts_and_ends_with_parenthesises =
                is_open_parentheses(chunk[0])
                && is_close_parenthesis(chunk[last_position]);
        if (starts_and_ends_with_parenthesises) {
            int parenthesis_counter = 0;
            for (int i = 1; i < last_position; ++i) {
                const char symbol = chunk[i];
                if (is_open_parentheses(symbol)) {
                    parenthesis_counter++;
                }
                if (is_close_parenthesis(symbol)) {
                    parenthesis_counter--;
                }
                if (parenthesis_counter == -1) {
                    throw_error("IF_SPIDER: invalid if condition!");
                }
            }
            if (parenthesis_counter == 0) {
                spider_protocol[AIO_SCOPE_INDEX] = AIO_TRUE_BODY_SCOPE;
                *spider_pointer_reference = position + 1;
                string if_condition = squeeze_string(chunk);
                add_string_in_list(materials[AIO_IF_CONDITION_INDEX], if_condition);
                return TRUE;
            } else {
                throw_error("IF_SPIDER: invalid if condition!");
            }
        }
    }
    return FALSE;
}

/**
 * Weaving.
 */

void weave_if_instruction_for(aio_instruction_holder *instruction_holder, int *next_ripper_point_reference,
                              struct aio_spider *spider) {
    if (is_ready_for_weaving) {
    } else {
        throw_error("ASSIGN SPIDER: not ready for weaving!");
    }
}