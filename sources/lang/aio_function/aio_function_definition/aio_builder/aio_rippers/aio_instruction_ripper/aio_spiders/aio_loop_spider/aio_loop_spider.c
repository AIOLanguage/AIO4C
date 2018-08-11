#include <malloc.h>
#include <mem.h>
#include <ctype.h>
#include "../../../../../../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_spiders/aio_spider.h"
#include "../../../../../../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"
#include "../../../../../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../../../../../headers/lib/utils/string_utils/string_builder.h"
#include "../../../../../../../../../headers/lib/point_watcher/point_watcher.h"
#include "../../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_spiders/aio_spider_swarm.h"
#include "../../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_spiders/aio_loop_spider/aio_inner_spiders/aio_default_loop_header_spider.h"
#include "../../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_spiders/aio_loop_spider/aio_inner_spiders/aio_in_loop_header_spider.h"
#include "../../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_spiders/aio_loop_spider/aio_inner_spiders/aio_tiny_loop_header_spider.h"

#define AIO_NUMBER_OF_SPIDERS 3

#define AIO_DOUBLE_STRING_SPIDER "DOUBLE_STRING_SPIDER"

/**
 * Declare functions.
 */

const_boolean is_end_of_body(const_string function_body_string, point_watcher *watcher);

const aio_spider_message is_found_loop_instruction(const_string string_web, aio_spider *spider);

void handle_loop_modifier_scope(const_string string_web, aio_spider *spider);

void handle_loop_header_scope(const_string string_web, aio_spider *spider);

aio_spider_swarm *breed_aio_loop_header_spider_swarm();

void handle_loop_body_scope(const_string string_web, aio_spider *spider);

void dig_header_materials(const_string string_web, aio_spider *parent_spider);

void weave_loop_instruction_for(aio_instruction_holder *instruction_holder, const_string source_code,
                                int *next_ripper_point_reference, aio_spider *spider);

/**
 * Reset.
 */

void reset_loop_spider(aio_spider *spider) {
    aio_loop_materials *materials = spider->get.loop_materials;
    //Reset point watchers:
    reset_point_watcher(materials->main_watcher);
    reset_point_watcher(materials->header_watcher);
    reset_point_watcher(materials->body_watcher);
    //Reset state:
    materials->scope_type = AIO_LOOP_MODIFIER_SCOPE;
    materials->body_type = AIO_LOOP_UNDEFINED_BODY;
    materials->header_scope_type = AIO_LOOP_HEADER_DEFINE;
    //Free materials:
    free_strings_in_list(materials->pointer_data_list);
    free(materials->start_variable);
    free(materials->start_value);
    free(materials->condition);
    free(materials->changeable_variable);
    free(materials->step_value);
}

/**
 * Destructor.
 */

void free_loop_spider(aio_spider *spider) {
    reset_loop_spider(spider);
    aio_loop_materials *materials = spider->get.loop_materials;
    free(materials->main_watcher);
    free(materials->header_watcher);
    free(materials->body_watcher);
    free_string_list(materials->pointer_data_list);
    free(materials);
    free(spider);
}

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
    //Create materials:
    aio_loop_materials *materials = calloc(1, sizeof(aio_loop_materials));
    materials->main_watcher = new_point_watcher();
    materials->header_watcher = new_point_watcher();
    materials->body_watcher = new_point_watcher();
    //Init state:
    materials->scope_type = AIO_LOOP_MODIFIER_SCOPE;
    materials->body_type = AIO_LOOP_UNDEFINED_BODY;
    materials->header_scope_type = AIO_LOOP_HEADER_DEFINE;
    //Init pointer data:
    materials->pointer_data_list = new_string_list();
    //Set materials:
    spider->get.loop_materials = materials;
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    return spider;
}

const aio_spider_message is_found_loop_instruction(const_string string_web, aio_spider *spider) {
    //Extract spider fields:
    const aio_loop_materials *materials = spider->get.loop_materials;
    const aio_loop_scope_type scope_type = materials->scope_type;
    point_watcher *main_watcher = materials->main_watcher;
    main_watcher->end_index++;
    //Prepare to scanning:
    const char last_symbol = string_web[main_watcher->end_index - 1];
    //Spider waits string data:
    if (main_watcher->mode == POINT_PASSIVE_MODE) {
        if (is_space_or_line_break(last_symbol)) {
            //Spider waiting:
            main_watcher->start_index++;
        } else {
            //Spider is ready for analysing:
            main_watcher->mode = POINT_ACTIVE_MODE;
        }
    }
    //Spider works:
    if (main_watcher->mode == POINT_ACTIVE_MODE) {
        switch (scope_type) {
            case AIO_LOOP_MODIFIER_SCOPE:
                handle_loop_modifier_scope(string_web, spider);
                break;
            case AIO_LOOP_HEADER_SCOPE:
                handle_loop_header_scope(string_web, spider);
                break;
            case AIO_LOOP_BODY_SCOPE:
                handle_loop_body_scope(string_web, spider);
                break;
            case AIO_LOOP_WEAVING_SCOPE:
                break;
        }
    }
    return spider->message;
}

void handle_loop_modifier_scope(const_string string_web, aio_spider *spider) {
    aio_loop_materials *materials = spider->get.loop_materials;
    point_watcher *watcher = materials->main_watcher;
    const char last_symbol = string_web[watcher->end_index - 1];
    if (is_space_or_line_break(last_symbol)) {
        const int start_index = watcher->start_index;
        const int end_index = watcher->end_index;
        const int hold_positions = end_index - start_index;
        if (hold_positions == 3) {
            const_boolean is_loop_modifier =
                    string_web[start_index] == 'l'
                    && string_web[start_index + 1] == 'o'
                    && string_web[start_index + 2] == 'o';
            if (is_loop_modifier) {
                //Shift watcher:
                watcher->start_index = end_index;
                watcher->mode = POINT_PASSIVE_MODE;
                //Set scope:
                materials->scope_type = AIO_LOOP_HEADER_SCOPE;
                //Set message:
                spider->message = AIO_SPIDER_FOUND_MATERIALS;
            }
        }
    }
}

void handle_loop_header_scope(const_string string_web, aio_spider *spider) {
    aio_loop_materials *materials = spider->get.loop_materials;
    point_watcher *main_watcher = materials->main_watcher;
    point_watcher *header_watcher = materials->header_watcher;
    //Define last position:
    const int last_position = main_watcher->end_index - 1;
    const char last_symbol = string_web[last_position];
    //Scanning:
    const_boolean is_passive = header_watcher->mode == POINT_PASSIVE_MODE;
    const_boolean is_active = header_watcher->mode == POINT_ACTIVE_MODE;
    const_boolean is_whitespace_cond = is_space_or_line_break(last_symbol);
    const_boolean is_open_parenthesis_cond = is_open_parenthesis(last_symbol);
    const_boolean is_close_parenthesis_cond = is_close_parenthesis(last_symbol);
    //Meet open parenthesis:
    if (is_open_parenthesis_cond) {
        //Start of loop header:
        if (is_passive) {
            //Jump over open parenthesis:
            header_watcher->start_index = main_watcher->end_index;
            header_watcher->mode = POINT_ACTIVE_MODE;
        }
        //Parenthesis in condition:
        if (is_active) {
            //Count parentheses:
            header_watcher->pointer++;
        }
    }
    //Meet close parenthesis:
    if (is_close_parenthesis_cond) {
        //Doesn't start loop  header:
        if (is_passive) {
            throw_error("LOOP SPIDER: condition can not start with ')'");
        }
        //In loop header:
        if (is_active) {
            header_watcher->pointer--;
            //Parenthesis closes condition:
            if (header_watcher->pointer == 0) {
                //End of condition:
                //Doesn't hold close parenthesis:
                header_watcher->end_index = last_position;
                //Shift main watcher:
                main_watcher->start_index = main_watcher->end_index;
                main_watcher->mode = POINT_PASSIVE_MODE;
                //Set scope:
                materials->scope_type = AIO_LOOP_BODY_SCOPE;
                //Dig header materials:
                dig_header_materials(string_web, spider);
            }
        }
    }
    //Skip whitespaces before condition:
    if (!is_whitespace_cond && is_passive) {
        throw_error("IF SPIDER: invalid context after 'if' modifier!");
    }
}

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//HEADER ANALYSING START:

void dig_header_materials(const_string string_web, aio_spider *parent_spider) {
    aio_loop_materials *materials = parent_spider->get.loop_materials;
    point_watcher *header_watcher = materials->header_watcher;
    //Header watcher pointer is already useless. Thus we can use pointer again!
    header_watcher->pointer = header_watcher->start_index;
    if (header_watcher->end_index - header_watcher->start_index >= 0) {
        //Create spider swarm for searching instructions:
        aio_spider_swarm *spider_swarm = breed_aio_loop_header_spider_swarm();
        string_builder *str_builder = new_string_builder();
        //After weaving instruction need to check function body string rest:
        while (header_watcher->pointer < header_watcher->end_index) {
            const char symbol = string_web[header_watcher->pointer++];
            const_boolean is_active = header_watcher->mode == POINT_ACTIVE_MODE;
            const_boolean is_passive = header_watcher->mode == POINT_PASSIVE_MODE;
            //Check string content to define:
            //Do spiders need to search instructions or not?
            if (is_passive) {
                if (is_end_of_body(string_web, header_watcher)) {
                    break;
                }
            }
            //Active mode for spider swarm:
            if (is_active) {
                //Add symbol in string builder:
                append_char_to(str_builder, symbol);
                const_string substring_web = str_builder->string_value;
                //Give "string web" to spider swarm:
                const aio_spider_swarm_mode swarm_mode = spider_swarm->mode;
                if (swarm_mode == AIO_ALL_SPIDERS_WORK) {
                    for (int j = 0; j < AIO_NUMBER_OF_SPIDERS; ++j) {
                        aio_spider *child = spider_swarm->spiders[j];
                        //Spider try to match "string web" with it task:
                        const aio_spider_message message = child->is_found_instruction(substring_web, child);
                        if (message == AIO_SPIDER_FOUND_MATERIALS) {
                            spider_swarm->active_spider = child;
                            spider_swarm->mode = AIO_ONE_SPIDER_WORKS;
                            break;
                        }
                    }
                }
                if (swarm_mode == AIO_ONE_SPIDER_WORKS) {
                    aio_spider *child_spider = spider_swarm->active_spider;
                    const aio_spider_message message = child_spider->is_found_instruction(substring_web, child_spider);
                    if (message == AIO_SPIDER_IS_READY_FOR_WEAVING) {
                        //Spider takes current holder and weave for holder instruction:
                        child_spider->weave_materials_for(parent_spider, child_spider, string_web,
                                                          &header_watcher->start_index, AIO_LOOP_TASK);
                        //Reset spiders:
                        reset_aio_spiders(spider_swarm);
                        //Reset string builder:
                        reset_string_builder(str_builder);
                        //Shift watcher:
                        header_watcher->pointer = header_watcher->start_index;
                        header_watcher->mode = POINT_PASSIVE_MODE;
                    }
                }
            }
        }
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free_aio_spider_swarm(spider_swarm);
    } else {
        throw_error("LOOP SPIDER: loop header is empty!");
    }
}

typedef struct aio_loop_short_header_materials {

} aio_loop_short_header_materials;

aio_spider *new_aio_loop_short_spider() {
    
}

typedef struct aio_loop_shortest_header_materials {

} aio_loop_shortest_header_materials;

aio_spider *new_aio_loop_shortest_spider() {

}

typedef struct aio_loop_condition_spider {

} aio_loop_condition_spider;

aio_spider *new_aio_loop_condition_spider() {

}

aio_spider_swarm *breed_aio_loop_header_spider_swarm() {
    //Create spiders:
    aio_spider **spiders = calloc(AIO_NUMBER_OF_SPIDERS, sizeof(aio_spider *));
    spiders[0] = new_aio_default_loop_header_spider();
    spiders[1] = new_aio_in_loop_header_spider();
    spiders[2] = new_aio_tiny_loop_header_spider();
    aio_spider_swarm *swarm = calloc(1, sizeof(aio_spider_swarm));
    swarm->number_of_spiders = AIO_NUMBER_OF_SPIDERS;
    swarm->spiders = spiders;
    swarm->active_spider = NULL;
    swarm->mode = AIO_ALL_SPIDERS_WORK;
    return swarm;
}

//HEADER ANALYSING END:
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------


void handle_loop_body_scope(const_string string_web, aio_spider *spider) {

}

void weave_loop_instruction_for(aio_instruction_holder *instruction_holder, const_string source_code,
                                int *next_ripper_point_reference, struct aio_spider *spider) {
}