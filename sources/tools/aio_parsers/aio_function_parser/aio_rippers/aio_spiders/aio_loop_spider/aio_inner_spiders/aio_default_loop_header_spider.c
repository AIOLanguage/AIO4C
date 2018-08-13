#include <malloc.h>
#include <ctype.h>
#include "../../../../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"
#include "../../../../../../../../headers/lang/aio_core/aio_core.h"
#include "../../../../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../../../../headers/tools/aio_parsers/aio_function_parser/aio_rippers/aio_spiders/aio_spider.h"

/**
 * Declare functions.
 */

void refresh_default_loop_header_declaration_scope(aio_spider *spider, string chunk,
                                                   aio_default_loop_header_pointer_declaration_type type,
                                                   aio_spider_message message);

void handle_default_loop_header_declaration_scope(const_string string_web, aio_spider *spider);

void handle_default_loop_header_equal_sign_scope(const_string string_web, aio_spider *spider);

void handle_default_loop_header_value_scope(const_string string_web, aio_spider *spider);

void handle_default_loop_header_condition_scope(const_string string_web, aio_spider *spider);

void handle_default_loop_header_step_scope(const_string string_web, aio_spider *spider);

/**
 * Reset.
 */

void reset_default_loop_header_spider(aio_spider *spider) {

}

/**
 * Free spider.
 */

void free_default_loop_header_spider(aio_spider *spider) {

}

/**
 * Constructor.
 */

aio_spider *new_aio_default_loop_header_spider(aio_main_loop_materials *parent_materials) {

}

/**
 * Searching.
 */

const aio_spider_message is_found_default_loop_header_instruction(const_string string_web, aio_spider *spider) {
    //Extract spider fields:
    const aio_default_loop_header_materials *materials = spider->get.loop_materials->from.default_loop_header;
    const aio_default_loop_header_scope_type scope_type = materials->scope_type;
    point_watcher *main_watcher = materials->main_watcher;
    main_watcher->end_index++;
    //Prepare from scanning:
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
            case AIO_DEFAULT_LOOP_HEADER_DECLARATION_SCOPE:
                handle_default_loop_header_declaration_scope(string_web, spider);
                break;
            case AIO_DEFAULT_LOOP_HEADER_EQUAL_SIGN_SCOPE:
                handle_default_loop_header_equal_sign_scope(string_web, spider);
                break;
            case AIO_DEFAULT_LOOP_HEADER_VALUE_SCOPE:
                handle_default_loop_header_value_scope(string_web, spider);
                break;
            case AIO_DEFAULT_LOOP_HEADER_CONDITION_SCOPE:
                handle_default_loop_header_condition_scope(string_web, spider);
                break;
            case AIO_DEFAULT_LOOP_HEADER_STEP_SCOPE:
                handle_default_loop_header_step_scope(string_web, spider);
                break;
            case AIO_DEFAULT_LOOP_HEADER_WEAVING_SCOPE:
                break;
        }
    }
    return spider->message;
}

/**
 * Extra handlers:
 **/

void handle_default_loop_header_declaration_scope(const_string string_web, aio_spider *spider) {
    //Extract materials:
    aio_default_loop_header_materials *materials = spider->get.loop_materials->from.default_loop_header;
    aio_default_loop_header_pointer_declaration_type declaration_type = materials->declaration_type;
    point_watcher *main_watcher = materials->main_watcher;
    point_watcher *condition_watcher = materials->condition_watcher;
    //Check string web:
    const char last_symbol = string_web[main_watcher->end_index - 1];
    //If was word:
    if (is_space_or_line_break(last_symbol)) {
        string chunk = substring_by_point_watcher(string_web, main_watcher);
        //Check conditions:
        const_boolean is_mutable_modifier = is_aio_mutable_modifier(chunk);
        const_boolean is_type = contains_aio_type_in_set(chunk);
        const_boolean is_variable_name = is_word(chunk) && can_use_name(chunk);
        switch (declaration_type) {
            case AIO_DEFAULT_LOOP_HEADER_VARIABLE_UNDEFINED:
                //Maybe string is the "mu" modifier?
                if (is_mutable_modifier) {
                    refresh_default_loop_header_declaration_scope(spider, chunk,
                                                                  AIO_DEFAULT_LOOP_HEADER_WAS_MUTABLE_MODIFIER,
                                                                  AIO_SPIDER_FOUND_MATERIALS);
                }
                //Maybe string is a type?
                if (is_type) {
                    refresh_default_loop_header_declaration_scope(spider, chunk, AIO_DEFAULT_LOOP_HEADER_IMMUTABLE,
                                                                  AIO_SPIDER_FOUND_MATERIALS);
                }
                    //Maybe start of loop condition?
                else {
                    //Change declaration type:
                    materials->declaration_type = AIO_DEFAULT_LOOP_HEADER_ABSENT;
                    main_watcher->mode = POINT_UNDEFINED_MODE;
                    //Change scope:
                    materials->scope_type = AIO_DEFAULT_LOOP_HEADER_CONDITION_SCOPE;
                    //--------------------------------------------------------------------------------------------------
                    //찌꺼기 수집기 (Garbage collector):
                    free(chunk);
                }
                break;
            case AIO_DEFAULT_LOOP_HEADER_WAS_MUTABLE_MODIFIER:
                //Maybe string is a type?
                if (is_type) {
                    refresh_default_loop_header_declaration_scope(spider, chunk, AIO_DEFAULT_LOOP_HEADER_MUTABLE,
                                                                  AIO_SPIDER_FOUND_MATERIALS);
                }
                //Maybe string is a variable name?
                if (is_variable_name) {
                    refresh_default_loop_header_declaration_scope(spider, chunk, AIO_DEFAULT_LOOP_HEADER_REFERENCE,
                                                                  AIO_SPIDER_FOUND_MATERIALS);
                    //Change scope:
                    materials->scope_type = AIO_DEFAULT_LOOP_HEADER_EQUAL_SIGN_SCOPE;
                } else {
                    //Not a variable name:
                    throw_error("DEFAULT LOOP HEADER SPIDER: invalid type or variable name in loop header!");
                }
                break;
            case AIO_DEFAULT_LOOP_HEADER_IMMUTABLE:
                //Must be variable name:
                if (is_variable_name) {
                    refresh_default_loop_header_declaration_scope(spider, chunk, AIO_DEFAULT_LOOP_HEADER_IMMUTABLE,
                                                                  AIO_SPIDER_FOUND_MATERIALS);
                    //Change scope:
                    materials->scope_type = AIO_DEFAULT_LOOP_HEADER_EQUAL_SIGN_SCOPE;
                } else {
                    throw_error("DEFAULT LOOP HEADER SPIDER: invalid variable name in loop header!");
                }
                break;
            case AIO_DEFAULT_LOOP_HEADER_MUTABLE:
                //Must be variable name:
                if (is_variable_name) {
                    refresh_default_loop_header_declaration_scope(spider, chunk, AIO_DEFAULT_LOOP_HEADER_MUTABLE,
                                                                  AIO_SPIDER_FOUND_MATERIALS);
                    //Change scope:
                    materials->scope_type = AIO_DEFAULT_LOOP_HEADER_EQUAL_SIGN_SCOPE;
                } else {
                    throw_error("DEFAULT LOOP HEADER SPIDER: invalid variable name in loop header!");
                }
                break;
            default:
                throw_error("ASSIGN SPIDER: Unreachable case!");
        }
    }
    //Always change start position for condition main_watcher:
    condition_watcher->start_index = main_watcher->start_index;
}

void refresh_default_loop_header_declaration_scope(aio_spider *spider, string chunk,
                                                   aio_default_loop_header_pointer_declaration_type type,
                                                   aio_spider_message message) {
    //Extract materials:
    aio_default_loop_header_materials *materials = spider->get.loop_materials->from.default_loop_header;
    string_list *variable_data_list = materials->pointer_data_list;
    point_watcher *watcher = materials->main_watcher;
    //Change declaration type:
    materials->declaration_type = type;
    //Put "mu" modifier in list:
    add_string_in_list(variable_data_list, chunk);
    //Shift main_watcher:
    watcher->start_index = watcher->end_index;
    watcher->mode = POINT_PASSIVE_MODE;
    //Set message:
    spider->message = message;
}

void handle_default_loop_header_equal_sign_scope(const_string string_web, aio_spider *spider) {
    aio_default_loop_header_materials *materials = spider->get.loop_materials->from.default_loop_header;
    point_watcher *watcher = materials->main_watcher;
    const int start_scanning_index = watcher->start_index;
    const_boolean is_equal_sign_symbol = is_equal_sign(string_web[start_scanning_index]);
    if (is_equal_sign_symbol) {
        //Set value scope:
        materials->scope_type = AIO_DEFAULT_LOOP_HEADER_VALUE_SCOPE;
        //Shift start index from end index:
        watcher->start_index = watcher->end_index;
        watcher->mode = POINT_PASSIVE_MODE;
        //Set message:
        spider->message = AIO_SPIDER_FOUND_MATERIALS;
    } else {
        if (spider->message == AIO_SPIDER_FOUND_MATERIALS) {
            throw_error("ASSIGN SPIDER: invalid variable definition!");
        }
    }
}

void handle_default_loop_header_value_scope(const_string string_web, aio_spider *spider) {
    //Extract fields:
    aio_default_loop_header_materials *materials = spider->get.loop_materials->from.default_loop_header;
    point_watcher *main_watcher = materials->main_watcher;
    //Check last symbol:
    const int last_position = main_watcher->end_index - 1;
    const char last_symbol = string_web[last_position];
    const int hold_positions = main_watcher->end_index - main_watcher->start_index;
    //Try from find regex: "//w|)//s+//w|(|{":
    int whitespace_counter = 0;
    if (isalpha(last_symbol)
        || is_open_parenthesis(last_symbol)
        || is_open_brace(last_symbol) && hold_positions >= 3) {
        for (int i = last_position - 1; i > 0; --i) {
            const char symbol = string_web[i];
            const_boolean is_space_or_line_break_condition = is_space_or_line_break(symbol);
            if (is_space_or_line_break_condition) {
                whitespace_counter++;
            }
            if (!is_space_or_line_break_condition && whitespace_counter > 0) {
                if (isalnum(symbol) || is_close_parenthesis(symbol)) {
                    main_watcher->end_index = i;
                    materials->scope_type = AIO_DEFAULT_LOOP_HEADER_CONDITION_SCOPE;
                    materials->start_value = substring_by_point_watcher(string_web, main_watcher);
                    main_watcher->start_index = main_watcher->end_index;
                }
            }
        }
    }
}

void handle_default_loop_header_condition_scope(const_string string_web, aio_spider *spider) {
    //Extract materials:
    aio_default_loop_header_materials *materials = spider->get.loop_materials->from.default_loop_header;
    const aio_default_loop_header_pointer_declaration_type declaration_type = materials->declaration_type;
    point_watcher *main_watcher = materials->main_watcher;
    //Check string web:
    const int end_index = main_watcher->end_index;
    const int last_position = main_watcher->end_index - 1;
    const char last_symbol = string_web[last_position - 1];
    //Check conditions:
    point_watcher *condition_watcher = materials->condition_watcher;
    const_boolean in_loop_condition = condition_watcher->mode == POINT_PASSIVE_MODE;
    const_boolean after_loop_condition = condition_watcher->mode == POINT_ACTIVE_MODE;
    //Check symbol:
    const_boolean is_whitespace_cond = is_space_or_line_break(last_symbol);
    const_boolean is_close_parenthesis_cond = is_close_parenthesis(last_symbol);
    const_boolean is_letter_cond = isalpha(last_symbol);
    const_boolean is_letter_or_number_or_close_parenthesis_cond = isalnum(last_symbol) || is_close_parenthesis_cond;
    switch (declaration_type) {
        case AIO_DEFAULT_LOOP_HEADER_ABSENT:
        case AIO_DEFAULT_LOOP_HEADER_MUTABLE:
        case AIO_DEFAULT_LOOP_HEADER_REFERENCE: {
            if (end_index == materials->end_of_loop_header) {
                condition_watcher->end_index = end_index;
                string dirty_condition = substring_by_point_watcher(string_web, condition_watcher);
                string clean_condition = squeeze_string(dirty_condition);
                materials->loop_condition = clean_condition;
                materials->scope_type = AIO_DEFAULT_LOOP_HEADER_WEAVING_SCOPE;
                spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
                //------------------------------------------------------------------------------------------------------
                //찌꺼기 수집기 (Garbage collector):
                free(dirty_condition);
            }
        }
            break;
        case AIO_DEFAULT_LOOP_HEADER_IMMUTABLE: {
            if (is_letter_or_number_or_close_parenthesis_cond && in_loop_condition) {
                condition_watcher->mode = POINT_ACTIVE_MODE;
            }
            if (is_whitespace_cond && after_loop_condition) {
                condition_watcher->pointer++;
            }
            if (is_letter_cond && after_loop_condition) {
                condition_watcher->end_index = main_watcher->end_index - condition_watcher->pointer;
                string dirty_condition = substring_by_point_watcher(string_web, condition_watcher);
                string clean_condition = squeeze_string(dirty_condition);
                materials->loop_condition = clean_condition;
                materials->scope_type = AIO_DEFAULT_LOOP_HEADER_STEP_SCOPE;
                main_watcher->start_index = main_watcher->end_index;
                //------------------------------------------------------------------------------------------------------
                //찌꺼기 수집기 (Garbage collector):
                free(dirty_condition);
            } else {
                condition_watcher->mode = POINT_PASSIVE_MODE;
                condition_watcher->pointer = 0;
            }
        }
            break;
        default:
            throw_error("DEFAULT LOOP HEADER SPIDER: invalid loop header context!");
            break;
    }
}

void handle_default_loop_header_step_scope(const_string string_web, aio_spider *spider) {
    //Extract materials:
    aio_default_loop_header_materials *materials = spider->get.loop_materials->from.default_loop_header;
    point_watcher *main_watcher = materials->main_watcher;
    const aio_default_loop_header_step_type step_scope = materials->step_type;
    //Check string web:
    const char last_symbol = string_web[main_watcher->end_index - 1];
    //If was word:
    if (!isalnum(last_symbol)) {
        string chunk = substring_by_point_watcher(string_web, main_watcher);
        const_boolean is_variable_name = is_word(chunk) && can_use_name(chunk);
        switch (step_scope) {
            case AIO_DEFAULT_LOOP_HEADER_STEP_VARIABLE:
                //Must be variable name:
                if (is_variable_name) {
                    //Change declaration type:
                    materials->step_type = AIO_DEFAULT_LOOP_HEADER_STEP_EQUAL_SIGN_SCOPE;
                    //Shift main_watcher:
                    main_watcher->start_index = main_watcher->end_index;
                    main_watcher->mode = POINT_PASSIVE_MODE;
                    //Set message:
                    spider->message = AIO_SPIDER_FOUND_MATERIALS;
                } else {
                    throw_error("DEFAULT LOOP HEADER SPIDER: invalid variable name in loop header!");
                }
                break;
            case AIO_DEFAULT_LOOP_HEADER_STEP_EQUAL_SIGN_SCOPE:
                if (is_equal_sign(string_web[main_watcher->start_index])) {
                    //Set value scope:
                    materials->step_type = AIO_DEFAULT_LOOP_HEADER_STEP_VALUE_SCOPE;
                    //Shift start index from end index:
                    main_watcher->start_index = main_watcher->end_index;
                    main_watcher->mode = POINT_PASSIVE_MODE;
                    //Set message:
                    spider->message = AIO_SPIDER_FOUND_MATERIALS;
                }
                if (!is_space_or_line_break(last_symbol)) {
                    throw_error("ASSIGN SPIDER: invalid variable definition!");
                }
                break;
            case AIO_DEFAULT_LOOP_HEADER_STEP_VALUE_SCOPE: {
                //Get rest:
                string dirty_step_value = substring_by_point_watcher(string_web, main_watcher);
                string clean_step_value = squeeze_string(dirty_step_value);
            }
                break;
        }
    }
}