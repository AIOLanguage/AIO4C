#include <malloc.h>
#include <mem.h>
#include <ctype.h>
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

const int AIO_FALSE_BODY_SCOPE = 3;

const int AIO_IS_READY_FOR_WEAVING = 4;

/**
 * Branches.
 */

#define AIO_IF_BRANCHES_INDEX 1

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

const int AIO_STRING_WEB_INDEX = 1;

//----------------------------------------------------------------------------------------------------------------------

/**
 * Declare functions.
 */

void reset_if_spider(struct aio_spider *spider);

const enum aio_spider_message is_found_if_instruction(const_string string_web, aio_spider *spider);

void weave_if_instruction_for(aio_instruction_holder *holder, int *next_ripper_point_reference,
                              struct aio_spider *spider);

void free_if_spider(struct aio_spider *spider);

const_boolean handle_condition_scope(string chunk, int *spider_protocol, int *spider_pointer_reference,
                                     aio_spider_materials materials);

aio_instruction_holder *dig_aio_instruction_holder(const_string source_code, aio_instruction_holder *parent_holder,
                                                   const int start_position, const int end_position);

void save_string_web_in(aio_spider_materials materials, string string_web);

void handle_true_body(const_string chunk, int *spider_protocol, int *spider_pointer_reference) ;

void handle_false_body(const_string chunk, int *spider_protocol, int *spider_pointer_reference) ;

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
    protocol[AIO_IF_BRANCHES_INDEX] = AIO_UNDEFINED_BRANCHES;
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
    int *start_scan_position_reference = &spider->start_pointer;
    int *spider_protocol = spider->spider_protocol;
    aio_spider_materials materials = spider->collected_materials;
    //Extract protocol:
    const int scanning_scope = spider_protocol[AIO_SCOPE_INDEX];
    //Save string web:
    save_string_web_in(materials, (string) string_web);
    //Prepare to scanning:
    const size_t string_web_length = strlen(string_web);
    //Catch "if" modifier:
    const_boolean is_if_scanning_scope = scanning_scope == AIO_IF_SCOPE;
    if (is_if_scanning_scope) {
        if (is_aio_if_modifier(string_web)) {
            spider_protocol[AIO_SCOPE_INDEX] = AIO_CONDITION_SCOPE;
            *start_scan_position_reference = 2;
            return AIO_SPIDER_FOUND_MATERIALS;
        } else {
            return AIO_SPIDER_NOT_FOUND_MATERIALS;
        }
    } else {
        //Scan string web:
        const int start_point = *start_scan_position_reference;
        //Extract necessary part of string web:
        string chunk = substring(string_web, start_point, string_web_length);
        switch (scanning_scope) {
            //Condition scope:
            case 1:
                handle_condition_scope(chunk, spider_protocol, start_scan_position_reference, materials);
                break;
                //True body scope;
            case 2:
                handle_true_body(chunk, spider_protocol, start_scan_position_reference);
                break;
                //False body scope
            case 4:
                handle_false_body(chunk, spider_protocol, start_scan_position_reference);
                break;
                //Unreachable case:
            default:
                break;
        }
    }
    return AIO_SPIDER_SEARCH_OTHER_MATERIALS;
}

void save_string_web_in(aio_spider_materials materials, string string_web) {
    //Bind input string in materials:
    string_list *material_list = materials[AIO_STRING_WEB_INDEX];
    if (material_list->size == 0) {
        add_string_in_list(material_list, string_web);
    } else {
        material_list->strings[0] = string_web;
    }
}

const_boolean handle_condition_scope(string chunk, int *spider_protocol, int *spider_pointer_reference,
                                     aio_spider_materials materials) {
    const size_t chunk_length = strlen(chunk);
    const int last_position = chunk_length - 1;
    if (chunk_length >= 3) {
        const_boolean starts_and_ends_with_parenthesises =
                is_open_parentheses(chunk[0])
                && is_close_parenthesis(chunk[last_position]);
        if (starts_and_ends_with_parenthesises) {
            //After that need to check inner parentheses:
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
            //Is valid inner parentheses:
            if (parenthesis_counter == 0) {
                spider_protocol[AIO_SCOPE_INDEX] = AIO_TRUE_BODY_SCOPE;
                *spider_pointer_reference = last_position + 1;
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

enum aio_hypothesis {
    AIO_UNDEFINED_HYPOTHESIS, AIO_HAS_FALSE_BODY, AIO_HAS_NOT_FALSE_BODY
};

//FIXME CODE DUPLICATION!!!
void handle_true_body(const_string chunk, int *spider_protocol, int *spider_pointer_reference) {
    const size_t chunk_length = strlen(chunk);
    const int last_position = chunk_length - 1;
    const char last_symbol = chunk[last_position];
    //Define hypothesis:
    enum aio_hypothesis hypothesis = AIO_UNDEFINED_HYPOTHESIS;
    const_boolean ends_with_colon = is_colon(last_symbol);
    const_boolean ends_with_expression_or_brace = isalnum(last_symbol)
                                                  || is_close_parenthesis(last_symbol)
                                                  || is_close_brace(last_symbol);
    //Prepare to scan from last instruction until close brace:
    int i = last_position - 1;
    for (i; i >= 0; --i) {
        const char symbol = chunk[i];
        if (!is_space_or_line_break(symbol)) {
            if (is_close_brace(symbol)) {
                if (ends_with_colon) {
                    hypothesis = AIO_HAS_FALSE_BODY;
                }
                if (ends_with_expression_or_brace) {
                    hypothesis = AIO_HAS_NOT_FALSE_BODY;
                }
                break;
            } else {
                return;
            }
        }
    }
    point_watcher *watcher = new_point_watcher();
    for (int j = 0; j <= i; j++) {
        const char symbol = chunk[j];
        if (is_open_brace(symbol)) {
            if (watcher->mode == POINT_PASSIVE_MODE) {
                watcher->mode = POINT_ACTIVE_MODE;
                watcher->start_index = j;
            }
            watcher->pointer++;
        }
        if (is_close_brace(symbol)) {
            if (watcher->mode == POINT_ACTIVE_MODE) {
                watcher->pointer--;
                if (watcher->pointer == 0) {
                    watcher->end_index = j;
                    break;
                }
            } else {
                throw_error("IF SPIDER: incorrect placed braces!");
            }
        }
    }
    //Matches braces in position:
    if (watcher->end_index == i) {
        //Write in protocol true body bounds:
        spider_protocol[AIO_START_TRUE_POSITION_INDEX] = watcher->start_index;
        spider_protocol[AIO_END_TRUE_POSITION_INDEX] = watcher->end_index;
        //Set new start position:
        *spider_pointer_reference = last_position;
        //Check hypothesis:
        switch (hypothesis) {
            case AIO_HAS_FALSE_BODY:
                spider_protocol[AIO_SCOPE_INDEX] = AIO_FALSE_BODY_SCOPE;
                spider_protocol[AIO_IF_BRANCHES_INDEX] = AIO_HAS_TRUE_AND_FALSE_BRANCHES;
                break;
            case AIO_HAS_NOT_FALSE_BODY:
                spider_protocol[AIO_SCOPE_INDEX] = AIO_IS_READY_FOR_WEAVING;
                spider_protocol[AIO_IF_BRANCHES_INDEX] = AIO_HAS_TRUE_BRANCH;
                break;
            case AIO_UNDEFINED_HYPOTHESIS:
                throw_error("IF SPIDER: incorrect placed braces!");
        }
    } else {
        throw_error("IF SPIDER: incorrect placed braces!");
    }
}

void handle_false_body(const_string chunk, int *spider_protocol, int *spider_pointer_reference) {
    const size_t chunk_length = strlen(chunk);
    const int last_position = chunk_length - 1;
    const char last_symbol = chunk[last_position];
    //Define hypothesis:
    const_boolean ends_with_expression_or_brace = isalnum(last_symbol)
                                                  || is_close_parenthesis(last_symbol)
                                                  || is_close_brace(last_symbol);
    //Prepare to scan from last instruction until close brace:
    int i = last_position - 1;
    for (i; i >= 0; --i) {
        const char symbol = chunk[i];
        if (!is_space_or_line_break(symbol)) {
            if (is_close_brace(symbol) && ends_with_expression_or_brace) {
                break;
            } else {
                return;
            }
        }
    }
    point_watcher *watcher = new_point_watcher();
    for (int j = 0; j <= i; j++) {
        const char symbol = chunk[j];
        if (is_open_brace(symbol)) {
            if (watcher->mode == POINT_PASSIVE_MODE) {
                watcher->mode = POINT_ACTIVE_MODE;
                watcher->start_index = j;
            }
            watcher->pointer++;
        }
        if (is_close_brace(symbol)) {
            if (watcher->mode == POINT_ACTIVE_MODE) {
                watcher->pointer--;
                if (watcher->pointer == 0) {
                    watcher->end_index = j;
                    break;
                }
            } else {
                throw_error("IF SPIDER: incorrect placed braces!");
            }
        }
    }
    //Matches braces in position:
    if (watcher->end_index == i) {
        //Write in protocol true body bounds:
        spider_protocol[AIO_START_FALSE_POSITION_INDEX] = watcher->start_index;
        spider_protocol[AIO_END_FALSE_POSITION_INDEX] = watcher->end_index;
        //Set new start position:
        *spider_pointer_reference = last_position;
        spider_protocol[AIO_SCOPE_INDEX] = AIO_IS_READY_FOR_WEAVING;
    } else {
        throw_error("IF SPIDER: incorrect placed braces!");
    }
}

/**
 * Weaving.
 */

void weave_if_instruction_for(aio_instruction_holder *holder, int *next_ripper_point_reference,
                              struct aio_spider *spider) {
    //Extract spider fields:
    int *protocol = spider->spider_protocol;
    aio_spider_materials materials = spider->collected_materials;
    const_boolean is_ready_for_weaving = protocol[AIO_SCOPE_INDEX] == AIO_IS_READY_FOR_WEAVING;
    if (is_ready_for_weaving) {
        *next_ripper_point_reference += spider->start_pointer;
        //Get spider's materials:
        const_string_array if_condition_materials = materials[AIO_IF_CONDITION_INDEX]->strings;
        //Get true-false chunk:
        const_string chunk = materials[AIO_STRING_WEB_INDEX]->strings[0];
        //Weave if instruction:
        const_string if_condition = new_string(if_condition_materials[0]);
        //Create if branches:
        const int start_true_body_position = protocol[AIO_START_TRUE_POSITION_INDEX];
        const int end_true_body_position = protocol[AIO_END_TRUE_POSITION_INDEX];
        aio_instruction_holder *true_holder = dig_aio_instruction_holder(chunk, holder, start_true_body_position,
                                                                         end_true_body_position);
        aio_instruction_holder *false_holder = NULL;
        const_boolean has_false_branch = protocol[AIO_IF_BRANCHES_INDEX] == AIO_HAS_TRUE_AND_FALSE_BRANCHES;
        if (has_false_branch) {
            const int start_false_body_position = protocol[AIO_START_FALSE_POSITION_INDEX];
            const int end_false_body_position = protocol[AIO_END_FALSE_POSITION_INDEX];
            false_holder = dig_aio_instruction_holder(chunk, holder, start_false_body_position,
                                                      end_false_body_position);
        }
        //Create if instruction:
        aio_instruction *if_instruction = new_aio_if_instruction(holder, if_condition, true_holder, false_holder);
        //Add if instruction in holder's instructions:
        aio_instruction_list *instruction_list = holder->instruction_list;
        add_aio_instruction_in_list(instruction_list, if_instruction);
        //Weaving complete!
    } else {
        throw_error("ASSIGN SPIDER: not ready for weaving!");
    }
}