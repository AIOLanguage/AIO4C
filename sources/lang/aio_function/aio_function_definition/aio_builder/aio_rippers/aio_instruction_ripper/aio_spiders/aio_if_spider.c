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

/**
 * Declare functions.
 */

const aio_spider_message is_found_if_instruction(const_string string_web, aio_spider *spider);

void handle_if_modifier_scope(const_string string_web, aio_spider *spider);

void handle_condition_scope(const_string string_web, aio_spider *spider);

void handle_true_body_scope(const_string string_web, aio_spider *spider);

void handle_false_body_scope(const_string string_web, aio_spider *spider);

void weave_if_instruction_for(aio_instruction_holder *holder, const_string source_code,
                              int *next_ripper_point_reference, aio_spider *spider);

/**
 * Reset.
 */

void reset_if_spider(aio_spider *spider) {
    aio_if_materials *materials = spider->get.if_materials;
    reset_point_watcher(materials->main_watcher);
    reset_point_watcher(materials->header_watcher);
    reset_point_watcher(materials->true_watcher);
    reset_point_watcher(materials->false_watcher);
    //Reset state:
    materials->scope_type = AIO_IF_MODIFIER_SCOPE;
    materials->branch_type = AIO_UNDEFINED_BRANCHES;
    free(materials->condition);
}

/**
 * Destructor.
 */

void free_if_spider(aio_spider *spider) {
    aio_if_materials *materials = spider->get.if_materials;
    free_point_watcher(materials->main_watcher);
    free_point_watcher(materials->header_watcher);
    free_point_watcher(materials->true_watcher);
    free_point_watcher(materials->false_watcher);
    free(materials->condition);
    free(materials);
    free(spider);
}

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
    //Create materials:
    aio_if_materials *materials = calloc(1, sizeof(aio_if_materials));
    materials->header_watcher = new_point_watcher();
    materials->true_watcher = new_point_watcher();
    materials->false_watcher = new_point_watcher();
    materials->scope_type = AIO_IF_MODIFIER_SCOPE;
    materials->branch_type = AIO_UNDEFINED_BRANCHES;
    //Set materials:
    spider->get.if_materials = materials;
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    return spider;
}

/**
 * Searching.
 */

const aio_spider_message is_found_if_instruction(const_string string_web, aio_spider *spider) {
    //Extract spider fields:
    const aio_if_materials *materials = spider->get.if_materials;
    const aio_if_scope_type scope_type = materials->scope_type;
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
            case AIO_IF_MODIFIER_SCOPE:
                handle_if_modifier_scope(string_web, spider);
                break;
            case AIO_IF_CONDITION_SCOPE:
                handle_condition_scope(string_web, spider);
                break;
            case AIO_IF_TRUE_BODY_SCOPE:
                handle_true_body_scope(string_web, spider);
                break;
            case AIO_IF_FALSE_BODY_SCOPE:
                handle_false_body_scope(string_web, spider);
                break;
            case AIO_IF_WEAVING_SCOPE:
                break;
        }
    }
    return spider->message;
}

void handle_if_modifier_scope(const_string string_web, aio_spider *spider) {
    aio_if_materials *materials = spider->get.if_materials;
    point_watcher *watcher = materials->main_watcher;
    const char last_symbol = string_web[watcher->end_index - 1];
    if (is_space_or_line_break(last_symbol)) {
        const int start_index = watcher->start_index;
        const int end_index = watcher->end_index;
        const int hold_positions = end_index - start_index;
        if (hold_positions == 2) {
            const_boolean is_if_modifier = string_web[start_index] == 'i' && string_web[start_index + 1] == 'f';
            if (is_if_modifier) {
                //Shift watcher:
                watcher->start_index = end_index;
                watcher->mode = POINT_PASSIVE_MODE;
                //Set scope:
                materials->scope_type = AIO_IF_CONDITION_SCOPE;
                //Set message:
                spider->message = AIO_SPIDER_FOUND_MATERIALS;
            }
        }
    }
}

void handle_condition_scope(const_string string_web, aio_spider *spider) {
    aio_if_materials *materials = spider->get.if_materials;
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
        //Start of condition:
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
        //Doesn't start condition:
        if (is_passive) {
            throw_error("IF SPIDER: condition can not start with ')'");
        }
        //In condition:
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
                materials->scope_type = AIO_IF_TRUE_BODY_SCOPE;
                //Extract condition:
                string dirty_condition = substring_by_point_watcher(string_web, header_watcher);
                string clean_condition = squeeze_string(dirty_condition);
                materials->condition = clean_condition;
            }
        }
    }
    //Skip whitespaces before condition:
    if (!is_whitespace_cond && is_passive) {
        throw_error("IF SPIDER: invalid context after 'if' modifier!");
    }
}

void handle_true_body_scope(const_string string_web, aio_spider *spider) {
    aio_if_materials *materials = spider->get.if_materials;
    point_watcher *main_watcher = materials->main_watcher;
    point_watcher *true_watcher = materials->true_watcher;
    //Define last position:
    const int last_position = main_watcher->end_index - 1;
    const char last_symbol = string_web[last_position];
    //Scanning:
    const_boolean is_passive = true_watcher->mode == POINT_PASSIVE_MODE;
    const_boolean is_active = true_watcher->mode == POINT_ACTIVE_MODE;
    const_boolean is_waiting_for_false_modifier = true_watcher->mode = POINT_UNDEFINED_MODE;
    const_boolean is_whitespace_cond = is_space_or_line_break(last_symbol);
    const_boolean is_open_brace_cond = is_open_brace(last_symbol);
    const_boolean is_close_brace_cond = is_close_brace(last_symbol);
    //Meet open brace:
    if (is_open_brace_cond) {
        //Start of true body:
        if (is_passive) {
            //Jump over open brace:
            true_watcher->start_index = main_watcher->end_index;
            true_watcher->mode = POINT_ACTIVE_MODE;
        }
        //Brace in body:
        if (is_active) {
            //Count parentheses:
            true_watcher->pointer++;
        }
    }
    //Meet close brace:
    if (is_close_brace_cond) {
        //Doesn't start body:
        if (is_passive) {
            throw_error("IF SPIDER: condition can not start with ')'");
        }
        //In true body:
        if (is_active) {
            true_watcher->pointer--;
            //Brace closes true body:
            if (true_watcher->pointer == 0) {
                //End of true body:
                //Doesn't hold close brace:
                true_watcher->end_index = last_position;
            }
        }
    }
    //Skip whitespaces before condition:
    if (!is_whitespace_cond) {
        if (is_passive) {
            throw_error("IF SPIDER: invalid context after 'if' condition!");
        }
        if (is_waiting_for_false_modifier) {
            //Meet colon that is 'false' modifier:
            if (is_colon(last_symbol)) {
                //Set branch type:
                materials->branch_type = AIO_HAS_TRUE_AND_FALSE_BRANCHES;
                //Set scope:
                materials->scope_type = AIO_IF_FALSE_BODY_SCOPE;
            } else {
                //Set branch type:
                materials->branch_type = AIO_HAS_TRUE_BRANCH;
                //Set scope:
                materials->scope_type = AIO_IF_WEAVING_SCOPE;
                //Set message:
                spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
            }
            //Shift main watcher:
            main_watcher->start_index = main_watcher->end_index;
            main_watcher->mode = POINT_PASSIVE_MODE;
        }
    }
}

void handle_false_body_scope(const_string string_web, aio_spider *spider) {
    aio_if_materials *materials = spider->get.if_materials;
    point_watcher *main_watcher = materials->main_watcher;
    point_watcher *false_watcher = materials->false_watcher;
    //Define last position:
    const int last_position = main_watcher->end_index - 1;
    const char last_symbol = string_web[last_position];
    //Scanning:
    const_boolean is_passive = false_watcher->mode == POINT_PASSIVE_MODE;
    const_boolean is_active = false_watcher->mode == POINT_ACTIVE_MODE;
    const_boolean is_whitespace_cond = is_space_or_line_break(last_symbol);
    const_boolean is_open_brace_cond = is_open_brace(last_symbol);
    const_boolean is_close_brace_cond = is_close_brace(last_symbol);
    //Meet open brace:
    if (is_open_brace_cond) {
        //Start of true body:
        if (is_passive) {
            //Jump over open brace:
            false_watcher->start_index = main_watcher->end_index;
            false_watcher->mode = POINT_ACTIVE_MODE;
        }
        //Brace in body:
        if (is_active) {
            //Count parentheses:
            false_watcher->pointer++;
        }
    }
    //Meet close brace:
    if (is_close_brace_cond) {
        //Doesn't start body:
        if (is_passive) {
            throw_error("IF SPIDER: condition can not start with ')'");
        }
        //In true body:
        if (is_active) {
            false_watcher->pointer--;
            //Brace closes true body:
            if (false_watcher->pointer == 0) {
                //End of true body:
                //Doesn't hold close brace:
                false_watcher->end_index = last_position;
                //Set scope:
                materials->scope_type = AIO_IF_WEAVING_SCOPE;
                //Set message:
                spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
                //Shift main watcher:
                main_watcher->start_index = main_watcher->end_index;
                main_watcher->mode = POINT_PASSIVE_MODE;
            }
        }
    }
    //Skip whitespaces before condition:
    if (!is_whitespace_cond && is_passive) {
        throw_error("IF SPIDER: invalid context after 'if' condition!");
    }
}

/**
 * Weaving.
 */

void weave_if_instruction_for(aio_instruction_holder *holder, const_string source_code,
                              int *next_ripper_point_reference, aio_spider *spider) {
    //Extract spider fields:
    const aio_if_materials *materials = spider->get.if_materials;
    const point_watcher *main_watcher = materials->main_watcher;
    const point_watcher *true_watcher = materials->true_watcher;
    const point_watcher *false_watcher = materials->false_watcher;
    const aio_if_branch_type branch_type = materials->branch_type;
    const_boolean is_ready_for_weaving = materials->scope_type == AIO_IF_WEAVING_SCOPE;
    if (is_ready_for_weaving) {
        *next_ripper_point_reference += main_watcher->end_index;
        //Weave if instruction:
        const_string if_condition = new_string(materials->condition);
        aio_instruction_holder *true_holder = NULL;
        aio_instruction_holder *false_holder = NULL;
        switch (branch_type) {
            case AIO_UNDEFINED_BRANCHES:
                throw_error("IF SPIDER: bug in 'handle_true_body_scope' function!");
            case AIO_HAS_TRUE_AND_FALSE_BRANCHES: {
                const int start_position = false_watcher->start_index;
                const int end_position = false_watcher->end_index;
                false_holder = dig_aio_instruction_holder(source_code, holder, start_position, end_position);
            }
            case AIO_HAS_TRUE_BRANCH: {
                const int start_position = true_watcher->start_index;
                const int end_position = true_watcher->end_index;
                true_holder = dig_aio_instruction_holder(source_code, holder, start_position, end_position);
            }
        }
        aio_instruction *if_instruction = new_aio_if_instruction(holder, if_condition, true_holder, false_holder);
        //Add if instruction in holder's instructions:
        aio_instruction_list *instruction_list = holder->instruction_list;
        add_aio_instruction_in_list(instruction_list, if_instruction);
        //Weaving complete!
    } else {
        throw_error("IF SPIDER: not ready for weaving!");
    }
}