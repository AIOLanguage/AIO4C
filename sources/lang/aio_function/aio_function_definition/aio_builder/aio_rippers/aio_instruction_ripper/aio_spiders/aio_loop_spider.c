#include <malloc.h>
#include <mem.h>
#include <ctype.h>
#include "../../../../../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_spider/aio_spiders.h"
#include "../../../../../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"
#include "../../../../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../../../../headers/lib/utils/string_utils/string_builder.h"
#include "../../../../../../../../headers/lib/point_watcher/point_watcher.h"

//----------------------------------------------------------------------------------------------------------------------
//PROTOCOL:

#define AIO_NUMBER_OF_PROTOCOL_CELLS 6

/**
 * Scopes.
 */

#define AIO_SCOPE_INDEX 0

const int AIO_LOOP_SCOPE = 0;

const int AIO_LOOP_HEADER_SCOPE = 1;

const int AIO_LOOP_BODY_SCOPE = 2;

const int AIO_IF_WEAVING_SCOPE = 3;

/**
 * Body.
 */

#define AIO_LOOP_BODY_INDEX 1

const int AIO_UNDEFINED_BODY = 0;

const int AIO_HAS_BODY = 1;

/**
 * Start & end loop body bounds.
 */


/**
 * Header.
 */

#define AIO_START_HEADER_INDEX 2

#define AIO_END_HEADER_INDEX

#define AIO_HEADER_COUNTER_INDEX 4

/**
 * Body
 */

#define AIO_START_BODY_POSITION_INDEX 5

#define AIO_END_BODY_POSITION_INDEX 6

#define AIO_BODY_COUNTER_INDEX 7

//----------------------------------------------------------------------------------------------------------------------
//MATERIALS:

#define AIO_NUMBER_OF_MATERIALS 5

const int AIO_POINTER_DEFINITION_INDEX = 0;

const int AIO_START_VALUE_INDEX = 1;

const int AIO_CONDITION_INDEX = 2;

const int AIO_STEP_INDEX = 3;

const int AIO_STRING_WEB_INDEX = 4;

//----------------------------------------------------------------------------------------------------------------------

/**
 * Declare functions.
 */

void reset_loop_spider(struct aio_spider *spider);

const_boolean is_found_loop_instruction(const_string string_web, aio_spider *spider);

void weave_loop_instruction_for(aio_instruction_holder *holder, int *next_ripper_point_reference,
                                struct aio_spider *spider);

void free_loop_spider(struct aio_spider *spider);

void
handle_loop_header_scope(const_string string_web, aio_spider *spider, const int end_position);

/**
 * Constructor.
 */

aio_spider *new_aio_loop_spider() {
    aio_spider *spider = calloc(1, sizeof(aio_spider));
    //Bind main spider's functions:
    spider->reset = reset_loop_spider;
    spider->is_found_instruction = is_found_loop_instruction;
    spider->weave_instruction_for = weave_loop_instruction_for;
    spider->free = free_loop_spider;
    //Init start scanning position:
    spider->start_scanning_position = 0;
    //Create spider's protocol:
    spider->spider_protocol = calloc(AIO_NUMBER_OF_PROTOCOL_CELLS, sizeof(int));
    //Create spider materials:
    spider->collected_materials = new_aio_spider_materials(AIO_NUMBER_OF_MATERIALS);
    return spider;
}

/**
 * Reset.
 */

void reset_loop_spider(struct aio_spider *spider) {
    spider->start_scanning_position = 0;
    //Reset protocol:
    int *protocol = spider->spider_protocol;
    protocol[AIO_SCOPE_INDEX] = AIO_LOOP_SCOPE;
    protocol[AIO_LOOP_BODY_INDEX] = AIO_UNDEFINED_BODY;
    protocol[AIO_START_BODY_POSITION_INDEX] = -1;
    protocol[AIO_END_BODY_POSITION_INDEX] = -1;
    protocol[AIO_HEADER_COUNTER_INDEX] = 0;
    protocol[AIO_BODY_COUNTER_INDEX] = 0;
    reset_aio_spider_materials(spider->collected_materials, AIO_NUMBER_OF_MATERIALS);
}

/**
 * Destructor.
 */

void free_loop_spider(struct aio_spider *spider) {
    free(spider->spider_protocol);
    for (int i = 0; i < AIO_NUMBER_OF_MATERIALS; ++i) {
        string_list *material_list = spider->collected_materials[i];
        free_string_list(material_list);
    }
    free(spider);
}


const_boolean is_found_loop_instruction(const_string string_web, aio_spider *spider) {
    //Extract spider materials:
    int *protocol = spider->spider_protocol;
    aio_spider_materials materials = spider->collected_materials;
    //Save string web in materials:
    save_string_web_in(materials, (string) string_web, AIO_STRING_WEB_INDEX);
    //Define string web length:
    const size_t string_web_length = strlen(string_web);
    //Catch loop modifier:
    const int scanning_scope = protocol[AIO_SCOPE_INDEX];
    const_boolean is_loop_scanning_scope = scanning_scope == AIO_LOOP_SCOPE;
    if (is_loop_scanning_scope) {
        if (is_aio_loop_modifier(string_web)) {
            protocol[AIO_SCOPE_INDEX] = AIO_LOOP_HEADER_SCOPE;
            spider->start_scanning_position = 2;
            return AIO_SPIDER_FOUND_MATERIALS;
        } else {
            return AIO_SPIDER_NOT_FOUND_MATERIALS;
        }
    } else {
        //Scan string web:
        const int end_position = string_web_length - 1;
        switch (scanning_scope) {
            //Pointer scope:
            case 1:
                handle_loop_header_scope(string_web, spider, end_position);
                break;
                //Mandatory condition scope:
            case 4:
                handle_loop_body_scope(string_web, end_position, materials);
                break;
                //Unreachable case:
            default:
                break;
        }
    }
    return AIO_SPIDER_SEARCH_OTHER_MATERIALS;
}

void handle_loop_header_scope(const_string string_web, aio_spider *spider, const int end_position) {
    //Extract spider fields:
    int *protocol = spider->spider_protocol;
    int i = spider->start_scanning_position;
    aio_spider_materials materials = spider->collected_materials;
    //Check parentheses:
    const char last_symbol = string_web[end_position];
    if (is_open_parenthesis(last_symbol)) {
        protocol[AIO_HEADER_COUNTER_INDEX]++;
    }
    if (is_close_parenthesis(last_symbol)) {
        protocol[AIO_HEADER_COUNTER_INDEX]--;
        const int parenthesis_counter = protocol[AIO_HEADER_COUNTER_INDEX];
        if (parenthesis_counter == 0){

        }
        if (parenthesis_counter < 0){
            throw_error("LOOP SPIDER: invalid loop header!");
        }
    }
    //Go to start pointer definition:
    while (is_space_or_line_break(string_web[++i]));
    if (!is_open_parenthesis(string_web[i])) {

    }




    //If is loop header:
    if (last_parenthesis_position == end_position) {
        *start_position_ref



        //Create spider swarm for searching instructions:
        aio_spider_swarm *spider_swarm = breed_aio_loop_spider_swarm();
        string_builder *str_builder = new_string_builder();
        //Start to find instruction:
        point_watcher *watcher = new_point_watcher();
        //After weaving instruction need to check function body string rest:
        boolean is_needed_check_body = TRUE;
        for (watcher->pointer = start_position; watcher->pointer < end_position; ++watcher->pointer) {
            const char symbol = source_code[watcher->pointer];
            //Check string content to define:
            //Do spiders need to search instructions or not?
            if (is_needed_check_body) {
                is_needed_check_body = FALSE;
                if (!has_function_content_rest(source_code, watcher->pointer, end_position)) {
                    break;
                } else {
                    watcher->mode = POINT_PASSIVE_MODE;
                }
            }
            //Skip whitespaces and line breaks:
            if (watcher->mode == POINT_PASSIVE_MODE) {
                if (is_space_or_line_break(symbol)) {
                    watcher->pointer++;
                } else {
                    watcher->mode = POINT_ACTIVE_MODE;
                }
            }
            //Active mode for spider swarm:
            if (watcher->mode == POINT_ACTIVE_MODE) {
                //Add symbol in string builder:
                append_char_to(str_builder, symbol);
                const_string string_web = str_builder->string_value;
                //Give "string web" to spider swarm:
                const enum aio_spider_swarm_mode swarm_mode = spider_swarm->mode;
                if (swarm_mode == AIO_ONE_SPIDER_WORKS) {
                    aio_spider *spider = spider_swarm->active_spider;
                    const enum aio_spider_message message = spider->is_found_instruction(string_web, spider);
                    if (message == AIO_SPIDER_WAS_CRUSH) {
                        throw_error("INSTRUCTION RIPPER: invalid context!");
                    }
                    if (message == AIO_SPIDER_IS_READY_FOR_WEAVING) {
                        //Spider takes current holder and weave for holder instruction:
                        spider->weave_instruction_for(current_holder, &watcher->start_index, spider);
                        reset_aio_spiders(spider_swarm);
                        reset_string_builder(str_builder);
                        watcher->pointer = watcher->start_index;
                        is_needed_check_body = TRUE;
                    }
                }
                if (swarm_mode == AIO_ALL_SPIDERS_WORK) {
                    for (int j = 0; j < AIO_NUMBER_OF_SPIDERS; ++j) {
                        aio_spider *spider = spider_swarm->spiders[j];
                        //Spider try to match "string web" with it task:
                        enum aio_spider_message message = spider->is_found_instruction(string_web, spider);
                        if (message == AIO_SPIDER_FOUND_MATERIALS) {
                            spider_swarm->active_spider = spider;
                            spider_swarm->mode = AIO_ONE_SPIDER_WORKS;
                        }
                        if (message == AIO_SPIDER_WAS_CRUSH) {
                            throw_error("INSTRUCTION RIPPER: invalid context!");
                        }
                    }
                }
            }
        }


    }






//
}


void handle_condition_scope(const_string string_web, int *start_position_ref, const int end_position,
                            aio_spider_materials materials) {

}

void weave_loop_instruction_for(aio_instruction_holder *holder, int *next_ripper_point_reference,
                                struct aio_spider *spider) {
}













//if (is_open_parenthesis(string_web[i])) {
//
//
//        i++;
//        while (is_space_or_line_break(string_web[i++]));
//        if (isalnum(string_web[i])) {
//            *start_position_ref = i;
//        } else {
//            throw_error("LOOP SPIDER: invalid loop header!");
//        }
//    }
//
//
//    const char last_symbol = string_web[end_position];
//    if (isalnum(last_symbol)) {
//        int whitespace_counter = 0;
//        for (int i = end_position; i >= *start_position_ref; --i) {
//            const char symbol = string_web[i];
//            if (is_space_or_line_break(symbol)) {
//                whitespace_counter++;
//            } else {
//                const_boolean ends_previous_definition = (isalnum(symbol) || is_close_parenthesis(symbol));
//                if (whitespace_counter > 0 && ends_previous_definition) {
//
//
//                } else {
//                    return;
//                }
//            }
//        }
//    } else {
//        return;
//    }