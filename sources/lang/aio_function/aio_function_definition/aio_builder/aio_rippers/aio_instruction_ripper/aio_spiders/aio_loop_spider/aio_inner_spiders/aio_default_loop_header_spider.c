#include <malloc.h>
#include <ctype.h>
#include "../../../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_spiders/aio_spider.h"
#include "../../../../../../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_spiders/aio_loop_spider/aio_inner_spiders/aio_default_loop_header_spider.h"
#include "../../../../../../../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"
#include "../../../../../../../../../../headers/lang/aio_core/aio_core.h"
#include "../../../../../../../../../../headers/lib/utils/error_utils/error_utils.h"

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

struct aio_spider *new_aio_default_loop_header_spider(aio_main_loop_materials *parent_materials) {

}

/**
 * Searching.
 */

const aio_spider_message is_found_default_loop_header_instruction(const_string string_web, aio_spider *spider) {
    //Extract spider fields:
    const aio_default_loop_header_materials *materials = spider->get.loop_materials->get.default_loop_header_materials;
    const aio_default_loop_header_scope_type scope_type = materials->scope_type;
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
    aio_default_loop_header_materials *materials = spider->get.loop_materials->get.default_loop_header_materials;
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
            case AIO_DEFAULT_LOOP_HEADER_UNDEFINED:
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
    aio_default_loop_header_materials *materials = spider->get.loop_materials->get.default_loop_header_materials;
    string_list *variable_data_list = materials->variable_data_list;
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
    aio_default_loop_header_materials *materials = spider->get.loop_materials->get.default_loop_header_materials;
    point_watcher *watcher = materials->main_watcher;
    const int start_scanning_index = watcher->start_index;
    const_boolean is_equal_sign_symbol = is_equal_sign(string_web[start_scanning_index]);
    if (is_equal_sign_symbol) {
        //Set value scope:
        materials->scope_type = AIO_DEFAULT_LOOP_HEADER_VALUE_SCOPE;
        //Shift start index to end index:
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
    aio_default_loop_header_materials *materials = spider->get.loop_materials->get.default_loop_header_materials;
    point_watcher *main_watcher = materials->main_watcher;
    //Check last symbol:
    const int last_position = main_watcher->end_index - 1;
    const char last_symbol = string_web[last_position];
    const int hold_positions = main_watcher->end_index - main_watcher->start_index;
    //Try to find regex: "//w|)//s+//w|(|{":
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
    aio_default_loop_header_materials *materials = spider->get.loop_materials->get.default_loop_header_materials;
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
            //Hypothesis 1: end of loop condition:
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

}

aio_variable_definition *create_local_variable_definition(const aio_assign_variable_declaration_type declaration_type,
                                                          const_string_array variable_materials) {
    string variable_name = NULL;
    string variable_type = NULL;
    boolean is_mutable = FALSE;
    switch (declaration_type) {
        case AIO_ASSIGN_WILL_DEFINED:
            variable_name = new_string(variable_materials[0]);
            variable_type = AIO_WILL_DEFINED;
            is_mutable = FALSE;
            break;
        case AIO_ASSIGN_REFERENCE:
            variable_name = new_string(variable_materials[1]);
            variable_type = VOID;
            is_mutable = TRUE;
            break;
            //Immutable mode:
        case AIO_ASSIGN_IMMUTABLE:
            variable_name = new_string(variable_materials[1]);
            variable_type = new_string(variable_materials[0]);
            is_mutable = FALSE;
            break;
            //Mutable by value mode:
        case AIO_ASSIGN_MUTABLE:
            variable_name = new_string(variable_materials[1]);
            variable_type = new_string(variable_materials[0]);
            is_mutable = TRUE;
            break;
        default:
            throw_error("ASSIGN SPIDER: undefined variable declaration mode for weaving!");
    }
    return new_aio_variable_definition(variable_name, variable_type, is_mutable);
}

void weave_default_loop_header_materials_for(aio_spider *dst_spider, aio_spider *src_spider,
                                             int *next_spider_point_reference) {
    //Extract source spider fields:
    const aio_assign_materials *src_materials = src_spider->get.assign_materials;
    const_string_array variable_data = src_materials->variable_data_list->strings;
    const_string value_string = src_materials->value;
    const point_watcher *watcher = src_materials->watcher;
    const aio_assign_variable_declaration_type declaration_type = src_materials->declaration_type;
    const_boolean is_ready_for_weaving = src_materials->scope_type == AIO_ASSIGN_WEAVING_SCOPE;
    if (is_ready_for_weaving) {
        *next_spider_point_reference += watcher->end_index;
        aio_loop_materials *dst_materials = dst_spider->get.loop_materials;
        aio_loop_header_scope_type header_scope_type = dst_materials->header_scope_type;
        aio_variable_definition *pointer_definition = create_local_variable_definition(declaration_type, variable_data);
        aio_instruction *assign_instruction = new_aio_assign_instruction(NULL, value_string, pointer_definition->name);
        switch (header_scope_type) {
            case AIO_LOOP_HEADER_DEFINE: {
                dst_materials->start_assign_instruction = assign_instruction;
                dst_materials->pointer_definition = pointer_definition;
            }
                break;
            case AIO_LOOP_HEADER_CONDITION:
                throw_error("ASSIGN SPIDER: Ops! It's a bug!");
                break;
            case AIO_LOOP_HEADER_STEP: {
                aio_variable_definition *dst_pointer_definition = dst_materials->pointer_definition;
                if (dst_pointer_definition->is_mutable_by_value) {
                    throw_error("ASSIGN SPIDER: mutable pointer can not be changed in loop header!");
                }
                dst_materials->step_assign_instruction = assign_instruction;
            }
        }
    } else {
        throw_error("ASSIGN SPIDER: not ready for weaving!");
    }
}