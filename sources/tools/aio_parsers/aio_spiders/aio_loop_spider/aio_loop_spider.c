#include <malloc.h>
#include <mem.h>
#include <ctype.h>
#include "../../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"
#include "../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../headers/lib/utils/string_utils/string_builder.h"
#include "../../../../../headers/lib/point_watcher/point_watcher.h"

#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"


#define AIO_NUMBER_OF_SPIDERS 1 //3

/**
 * 주 논리 (Business logic).
 */

#define AIO_LOOP_SPIDER_DEBUG

#define AIO_LOOP_SPIDER_TAG "AIO_LOOP_SPIDER"

#ifdef AIO_LOOP_SPIDER_DEBUG

#include "../../../../../headers/lib/utils/log_utils/log_utils.h"
#include "../../../../../headers/tools/aio_parsers/aio_spiders/aio_spider.h"
#include "../../../../../headers/tools/aio_parsers/aio_spiders/aio_loop_spider/aio_loop_spider.h"

#endif

void refresh_loop_spider(aio_spider *spider, point_watcher *ripper_watcher) {
#ifdef AIO_LOOP_SPIDER_DEBUG
    log_info(AIO_LOOP_SPIDER_TAG, "Start to refresh 'loop' spider...");
#endif
    //Refresh main materials:
    aio_main_loop_materials *materials = spider->get.loop_materials->from.main;
    materials->scope_type = AIO_LOOP_MODIFIER_SCOPE;
    materials->main_watcher->start_index = ripper_watcher->pointer;
    materials->main_watcher->end_index = ripper_watcher->pointer;
    materials->main_watcher->mode = POINT_PASSIVE_MODE;
    reset_point_watcher(materials->header_watcher);
    reset_point_watcher(materials->body_watcher);
    //Refresh applied materials:
    const aio_loop_material_type header_material_type = materials->applied_header_material_type;
    if (header_material_type == AIO_LOOP_MATERIALS_DEFAULT_HEADER) {
        aio_default_loop_header_materials *default_header_materials = materials->get_applied_materials_from
                .default_loop_header;
        refresh_default_loop_header_materials(default_header_materials, materials->header_watcher);
    }
    if (header_material_type == AIO_LOOP_MATERIALS_IN_HEADER) {

    }
    if (header_material_type == AIO_LOOP_MATERIALS_TINY_HEADER) {

    }
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
#ifdef AIO_LOOP_SPIDER_DEBUG
    log_info(AIO_LOOP_SPIDER_TAG, "Reset of 'loop' spider is complete!");
#endif
}

/**
 * 거미를 비우다 (Free spider).
 */

void free_loop_spider(aio_spider *spider) {
    aio_loop_materials *materials = spider->get.loop_materials;
    aio_main_loop_materials *main_loop_materials = materials->from.main;
    //Free applied header materials:
    const aio_loop_material_type header_material_type = main_loop_materials->applied_header_material_type;
    if (header_material_type == AIO_LOOP_MATERIALS_DEFAULT_HEADER) {
        aio_default_loop_header_materials *default_header_materials = main_loop_materials->get_applied_materials_from
                .default_loop_header;
        free(default_header_materials);
    }
    if (header_material_type == AIO_LOOP_MATERIALS_IN_HEADER) {

    }
    if (header_material_type == AIO_LOOP_MATERIALS_TINY_HEADER) {

    }
    //Free main materials:
    free_point_watcher(main_loop_materials->main_watcher);
    free_point_watcher(main_loop_materials->header_watcher);
    free_point_watcher(main_loop_materials->body_watcher);
    free(main_loop_materials);
    free(materials);
    free(spider);
}

/**
 * 건설자 (Constructor).
 */

aio_spider *new_aio_loop_spider(point_watcher *ripper_watcher) {
#ifdef AIO_LOOP_SPIDER_DEBUG
    log_info(AIO_LOOP_SPIDER_TAG, "Start to create 'loop' spider...");
#endif
    aio_spider *spider = new_object(sizeof(aio_spider));
    //함수들을 놓다 (Put functions):
    spider->refresh = refresh_loop_spider;
    spider->is_found_instruction = is_found_loop_instruction;
    spider->weave_instruction_for = weave_loop_instruction_for;
    spider->free = free_loop_spider;
    //재료들을 만들다 (Create materials):
    aio_loop_materials *materials = new_object(sizeof(aio_loop_materials));
    materials->type = AIO_LOOP_MATERIALS_MAIN;
    aio_main_loop_materials *main_loop_materials = new_object(sizeof(aio_main_loop_materials));
    main_loop_materials->scope_type = AIO_LOOP_MODIFIER_SCOPE;
    main_loop_materials->main_watcher = new_point_watcher();
    main_loop_materials->main_watcher->start_index = ripper_watcher->start_index;
    main_loop_materials->main_watcher->end_index = ripper_watcher->pointer;
    main_loop_materials->header_watcher = new_point_watcher();
    main_loop_materials->body_watcher = new_point_watcher();
    main_loop_materials->applied_header_material_type = AIO_LOOP_MATERIALS_UNDEFINED;
    materials->from.main = main_loop_materials;
    //재료들을 놓다 (Set materials):
    spider->get.loop_materials = materials;
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
#ifdef AIO_LOOP_SPIDER_DEBUG
    log_info(AIO_LOOP_SPIDER_TAG, "Loop spider was created!");
#endif
    return spider;
}

const aio_spider_message is_found_loop_instruction(const_string source_code, point_watcher *ripper_watcher,
                                                   aio_spider *spider) {
    //재료들을 추출하다 (Extract materials):
    const aio_main_loop_materials *materials = spider->get.loop_materials->from.main;
    point_watcher *main_watcher = materials->main_watcher;
    main_watcher->end_index = ripper_watcher->pointer;
    const char current_symbol = source_code[main_watcher->end_index];
#ifdef AIO_LOOP_SPIDER_DEBUG
    //log_info_char(AIO_LOOP_SPIDER_TAG, "Current symbol:", current_symbol);
#endif
    //TODO: 코드 복제 (Code duplication)!
    if (main_watcher->mode == POINT_PASSIVE_MODE) {
        if (is_space_or_line_break(current_symbol)) {
            main_watcher->start_index++;
        } else {
            main_watcher->mode = POINT_ACTIVE_MODE;
        }
    }
    if (main_watcher->mode == POINT_ACTIVE_MODE) {
        if (materials->scope_type == AIO_LOOP_MODIFIER_SCOPE) {
            handle_loop_modifier_scope(source_code, spider);
        }
        if (materials->scope_type == AIO_LOOP_HEADER_SCOPE) {
            handle_loop_header_scope(source_code, spider);
        }
        if (materials->scope_type == AIO_LOOP_BODY_SCOPE) {
            handle_loop_body_scope(source_code, spider);
        }
    }
    return spider->message;
}

void handle_loop_modifier_scope(const_string source_code, aio_spider *spider) {
    aio_main_loop_materials *materials = spider->get.loop_materials->from.main;
    point_watcher *main_watcher = materials->main_watcher;
    const int current_position = main_watcher->end_index;
    const char current_symbol = source_code[current_position];
    //Check current symbol:
    const_boolean is_opening_parenthesis_cond = is_opening_parenthesis(current_symbol);
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    if (is_whitespace_cond || is_opening_parenthesis_cond) {
        const int start_index = main_watcher->start_index;
        const int end_index = main_watcher->end_index;
        const int hold_positions = end_index - start_index;
        if (hold_positions == 3) {
            const_boolean is_loop_modifier =
                    source_code[start_index] == 'l'
                    && source_code[start_index + 1] == 'o'
                    && source_code[start_index + 2] == 'o';
            if (is_loop_modifier) {
                //Shift main_watcher:
                main_watcher->start_index = end_index;
                main_watcher->mode = POINT_PASSIVE_MODE;
                //Set scope:
                materials->scope_type = AIO_LOOP_HEADER_SCOPE;
                //Set message:
                spider->message = AIO_SPIDER_FOUND_MATERIALS;
#ifdef AIO_LOOP_SPIDER_DEBUG
                log_info(AIO_LOOP_SPIDER_TAG, "Found loop modifier!");
#endif
            }
        }
    }
}

void handle_loop_header_scope(const_string source_code, aio_spider *spider) {
    aio_main_loop_materials *materials = spider->get.loop_materials->from.main;
    point_watcher *main_watcher = materials->main_watcher;
    point_watcher *header_watcher = materials->header_watcher;
    //Define last position:
    const int current_position = main_watcher->end_index;
    const char current_symbol = source_code[current_position];
    //Check symbol:
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    const_boolean is_opening_parenthesis_cond = is_opening_parenthesis(current_symbol);
    const_boolean is_closing_parenthesis_cond = is_closing_parenthesis(current_symbol);
    //Meet opening parenthesis:
    if (is_opening_parenthesis_cond) {
        //Start of loop header:
        if (header_watcher->mode == POINT_PASSIVE_MODE) {
            //Start with opening parenthesis:
            header_watcher->start_index = main_watcher->end_index;
            header_watcher->mode = POINT_ACTIVE_MODE;
        }
        //Parenthesis inside loop header:
        if (header_watcher->mode == POINT_ACTIVE_MODE) {
            //Count parentheses:
            header_watcher->pointer++;
        }
    }
    //Meet closing parenthesis:
    if (is_closing_parenthesis_cond) {
        //Loop header doesn't start with closing parenthesis:
        if (header_watcher->mode == POINT_PASSIVE_MODE) {
            throw_error_with_tag(AIO_LOOP_SPIDER_TAG, "Loop condition can not start with open parenthesis!");
        }
        //Inside loop header:
        if (header_watcher->mode == POINT_ACTIVE_MODE) {
            header_watcher->pointer--;
            //Parenthesis closes header:
            if (header_watcher->pointer == 0) {
                //End of condition:
                header_watcher->end_index = main_watcher->end_index + 1;
                //Shift main main_watcher:
                main_watcher->start_index = main_watcher->end_index + 1;
                main_watcher->mode = POINT_PASSIVE_MODE;
                //Set scope:
                materials->scope_type = AIO_LOOP_BODY_SCOPE;
#ifdef AIO_LOOP_SPIDER_DEBUG
                const_string header_string = substring_by_point_watcher(source_code, header_watcher);
                log_info_string(AIO_LOOP_SPIDER_TAG, "Captured header:", header_string);
                free((void *) header_string);
#endif
                //Dig header materials:
                dig_header_materials(source_code, spider);
            }
        }
    }
    //Skip whitespaces before condition:
    if (!is_whitespace_cond && header_watcher->mode == POINT_PASSIVE_MODE) {
        throw_error_with_tag(AIO_LOOP_SPIDER_TAG, "Invalid context after 'loo' modifier!");
    }
}

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//HEADER ANALYSING START:

void dig_header_materials(const_string source_code, aio_spider *parent_spider) {
#ifdef AIO_LOOP_SPIDER_DEBUG
    log_info(AIO_LOOP_SPIDER_TAG, "Dig header materials...");
#endif
    aio_main_loop_materials *materials = parent_spider->get.loop_materials->from.main;
    point_watcher *header_watcher = materials->header_watcher;
    //Header main_watcher pointer is already useless. Thus we can use pointer again!
    header_watcher->pointer = header_watcher->start_index + 1;
    const_boolean is_not_empty_header = header_watcher->end_index - header_watcher->start_index > 0;
    if (is_not_empty_header) {
        //Create spider swarm for searching instructions:
        aio_spider_nest *spider_nest = (aio_spider_nest *) breed_aio_loop_header_spider_nest(header_watcher);
        //After weaving instruction need from check function body string rest:
        while (header_watcher->pointer < header_watcher->end_index) {
            if (header_watcher->mode == POINT_PASSIVE_MODE) {
                if (is_end_of_block_body(source_code, header_watcher)) {
                    break;
                } else {
                    refresh_aio_spiders(spider_nest, header_watcher);
                }
            }
            //Active mode for spider nest:
            if (header_watcher->mode == POINT_ACTIVE_MODE) {
                const aio_spider_nest_mode swarm_mode = spider_nest->mode;
                if (swarm_mode == AIO_ALL_SPIDERS_WORK) {
                    for (int j = 0; j < AIO_NUMBER_OF_SPIDERS; ++j) {
                        aio_spider *child_spider = spider_nest->spiders[j];
                        //Spider try from match "string web" with it task:
                        const aio_spider_message message
                                = child_spider->is_found_instruction(source_code, header_watcher, child_spider);
                        if (message == AIO_SPIDER_FOUND_MATERIALS) {
#ifdef AIO_LOOP_SPIDER_DEBUG
                            log_info(AIO_LOOP_SPIDER_TAG, "One loop header spider works:");
#endif
                            spider_nest->active_spider = child_spider;
                            spider_nest->mode = AIO_ONE_SPIDER_WORKS;
                            break;
                        }
                    }
                }
                if (swarm_mode == AIO_ONE_SPIDER_WORKS) {
                    aio_spider *child_spider = spider_nest->active_spider;
                    const aio_spider_message message
                            = child_spider->is_found_instruction(source_code, header_watcher, child_spider);
                    if (message == AIO_SPIDER_IS_READY_FOR_WEAVING) {
#ifdef AIO_LOOP_SPIDER_DEBUG
                        log_info(AIO_LOOP_SPIDER_TAG, "START WE-WE-WE");
#endif
                        //Spider takes current holder and weave for holder instruction:
                        child_spider->weave_materials_for(parent_spider, child_spider, source_code, header_watcher);
                        //Reset spiders:
                        refresh_aio_spiders(spider_nest, header_watcher);
                        header_watcher->mode = POINT_PASSIVE_MODE;
                        //거미 무리 리셋 (Spider nest refresh):
                        spider_nest->mode = AIO_ALL_SPIDERS_WORK;
                        spider_nest->active_spider = NULL;
#ifdef AIO_LOOP_SPIDER_DEBUG
                        log_info(AIO_LOOP_SPIDER_TAG, "All loop header spiders work:");
#endif
                    }
                }
            }
            header_watcher->pointer++;
        }
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free_aio_spider_swarm(spider_nest);
    } else {
        throw_error_with_tag(AIO_LOOP_SPIDER_TAG, "Loop header is empty!");
    }
}

struct aio_spider_nest *breed_aio_loop_header_spider_nest(point_watcher *header_watcher) {
    //Create spiders:
    aio_spider **spiders = calloc(AIO_NUMBER_OF_SPIDERS, sizeof(struct aio_spider *));
    spiders[0] = new_aio_default_loop_header_spider(header_watcher);
    //spiders[1] = new_aio_in_loop_header_spider();
    //spiders[2] = new_aio_tiny_loop_header_spider();
    aio_spider_nest *nest = new_object(sizeof(aio_spider_nest));
    nest->number_of_spiders = AIO_NUMBER_OF_SPIDERS;
    nest->spiders = spiders;
    nest->active_spider = NULL;
    nest->mode = AIO_ALL_SPIDERS_WORK;
    return (struct aio_spider_nest *) nest;
}

//HEADER ANALYSING END:
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

void handle_loop_body_scope(const_string string_web, aio_spider *spider) {

}

void weave_loop_instruction_for(aio_instruction_holder *instruction_holder, const_string source_code,
                                point_watcher *ripper_watcher, struct aio_spider *spider) {

}