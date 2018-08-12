#include <mem.h>
#include <ctype.h>
#include "../../../../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../../../headers/lib/point_watcher/point_watcher.h"
#include "../../../../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"
#include "../../../../../../../headers/lang/aio_core/aio_core.h"
#include "../../../../../../../headers/lib/utils/string_utils/string_builder.h"
#include "../../../../../../../headers/tools/aio_parsers/aio_function_parser/aio_rippers/aio_spiders/aio_assign_spider/aio_assign_spider.h"
#include "../../../../../../../headers/lib/utils/memory_utils/memory_utils.h"

/**
 * Declare functions.
 */

const aio_spider_message is_found_assign_instruction(const_string string_web, aio_spider *spider);

void handle_assign_declaration_scope(const_string string_web, aio_spider *spider);

void refresh_assign_declaration_scope(aio_spider *spider, string chunk, aio_assign_variable_declaration_type type,
                                      aio_spider_message message);

void handle_assign_equal_sign_scope(const_string string_web, aio_spider *spider);

void handle_assign_value_scope(const_string string_web, aio_spider *spider);

void weave_assign_instruction_for(aio_instruction_holder *holder, const_string _,
                                  int *next_ripper_point_reference, aio_spider *spider);

aio_variable_definition *create_local_variable_definition(const aio_assign_variable_declaration_type declaration_type,
                                                          const_string_array variable_materials);

#define AIO_ASSIGN_SPIDER_DEBUG

#define AIO_ASSIGN_SPIDER_TAG "AIO_ASSIGN_SPIDER"

#ifdef AIO_ASSIGN_SPIDER_DEBUG

#include "../../../../../../../headers/lib/utils/log_utils/log_utils.h"

#endif


/**
 * Reset.
 */

void reset_assign_spider(aio_spider *spider) {
    //Reset spider state:
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    //Reset materials:
    aio_assign_materials *materials = spider->get.assign_materials;
    reset_point_watcher(materials->main_watcher);
    reset_point_watcher(materials->value_watcher);
    materials->scope_type = AIO_ASSIGN_DECLARATION_SCOPE;
    materials->declaration_type = AIO_ASSIGN_UNDEFINED_DECLARATION;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free(materials->value);
    free_strings_in_list(materials->variable_data_list);
}

/**
 * Free spider.
 */

void free_assign_spider(aio_spider *spider) {
    aio_assign_materials *materials = spider->get.assign_materials;
    free_point_watcher(materials->main_watcher);
    free_point_watcher(materials->value_watcher);
    free_strings_in_list(materials->variable_data_list);
    free_string_list(materials->variable_data_list);
    free(materials->value);
    free(materials);
    free(spider);
}

/**
 * Constructor.
 */

struct aio_spider *new_aio_assign_spider(const int body_length) {
    aio_spider *spider = new_object(sizeof(aio_spider));
    //Bind spider's functions:
    spider->reset = reset_assign_spider;
    spider->is_found_instruction = is_found_assign_instruction;
    spider->weave_instruction_for = weave_assign_instruction_for;
    spider->free = free_assign_spider;
    //Create materials:
    aio_assign_materials *materials = new_object(sizeof(aio_assign_materials));
    materials->scope_type = AIO_ASSIGN_DECLARATION_SCOPE;
    materials->declaration_type = AIO_ASSIGN_UNDEFINED_DECLARATION;
    materials->main_watcher = new_point_watcher();
    materials->value_watcher = new_point_watcher();
    materials->variable_data_list = new_string_list();
    //Set ripper info:
    materials->function_body_length = body_length;
    //Set materials:
    spider->get.assign_materials = materials;
    //Init start message:
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    return spider;
}

/**
 * Searching.
 */

const aio_spider_message is_found_assign_instruction(const_string string_web, aio_spider *spider) {
#ifdef AIO_ASSIGN_SPIDER_DEBUG
    log_info(AIO_ASSIGN_SPIDER_TAG, "Start founding...");
#endif
    //Extract spider fields:
    const aio_assign_materials *materials = spider->get.assign_materials;
    point_watcher *watcher = materials->main_watcher;
    watcher->end_index++;
    //Prepare from scanning:
    const char last_symbol = string_web[watcher->end_index - 1];
//    log_info_char(AIO_ASSIGN_SPIDER_TAG, "Last symbol:", last_symbol);
    //Skip whitespaces:
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
        if (materials->scope_type == AIO_ASSIGN_DECLARATION_SCOPE) {
#ifdef AIO_ASSIGN_SPIDER_DEBUG
            log_info(AIO_ASSIGN_SPIDER_TAG, "AIO_ASSIGN_DECLARATION_SCOPE");
#endif
            handle_assign_declaration_scope(string_web, spider);
        }
        if (materials->scope_type == AIO_ASSIGN_EQUAL_SIGN_SCOPE) {
#ifdef AIO_ASSIGN_SPIDER_DEBUG
            log_info(AIO_ASSIGN_SPIDER_TAG, "AIO_ASSIGN_EQUAL_SIGN_SCOPE");
#endif
            handle_assign_equal_sign_scope(string_web, spider);
            return spider->message;
        }
        if (materials->scope_type == AIO_ASSIGN_VALUE_SCOPE) {
#ifdef AIO_ASSIGN_SPIDER_DEBUG
            log_info(AIO_ASSIGN_SPIDER_TAG, "AIO_ASSIGN_VALUE_SCOPE");
#endif
            handle_assign_value_scope(string_web, spider);
        }
    }
    return spider->message;
}

/**
 * Extra handlers:
 **/

void handle_assign_declaration_scope(const_string string_web, aio_spider *spider) {
    //Extract materials:
    aio_assign_materials *materials = spider->get.assign_materials;
    point_watcher *watcher = materials->main_watcher;
    //Check string web:
    const char last_symbol = string_web[watcher->end_index - 1];
    //If was word:
    if (is_space_or_line_break(last_symbol)) {
#ifdef AIO_ASSIGN_SPIDER_DEBUG
        log_info(AIO_ASSIGN_SPIDER_TAG, "Was whitespace!");
#endif
        string chunk = substring(string_web, watcher->start_index, watcher->end_index - 1);
#ifdef AIO_ASSIGN_SPIDER_DEBUG
        log_info_string(AIO_ASSIGN_SPIDER_TAG, "Chunk:", chunk);
#endif
        //Check conditions:
        const_boolean is_mutable_modifier = is_aio_mutable_modifier(chunk);
        const_boolean is_type = contains_aio_type_in_set(chunk);
        const_boolean is_variable_name = is_word(chunk) && can_use_name(chunk);
        if (materials->declaration_type == AIO_ASSIGN_UNDEFINED_DECLARATION) {
#ifdef AIO_ASSIGN_SPIDER_DEBUG
            log_info(AIO_ASSIGN_SPIDER_TAG, "AIO_ASSIGN_UNDEFINED_DECLARATION");
#endif
            //Maybe string is the "mu" modifier?
            if (is_mutable_modifier) {
#ifdef AIO_ASSIGN_SPIDER_DEBUG
                log_info_string(AIO_ASSIGN_SPIDER_TAG, "Put mutable modifier:", chunk);
#endif
                refresh_assign_declaration_scope(spider, chunk, AIO_ASSIGN_WAS_MUTABLE_MODIFIER,
                                                 AIO_SPIDER_FOUND_MATERIALS);
            }
            //Maybe string is a type?
            if (is_type) {
#ifdef AIO_ASSIGN_SPIDER_DEBUG
                log_info_string(AIO_ASSIGN_SPIDER_TAG, "Put type:", chunk);
#endif
                refresh_assign_declaration_scope(spider, chunk, AIO_ASSIGN_IMMUTABLE,
                                                 AIO_SPIDER_NOT_FOUND_MATERIALS);
            }
            //Maybe is a variable name?
            if (is_variable_name) {
#ifdef AIO_ASSIGN_SPIDER_DEBUG
                log_info_string(AIO_ASSIGN_SPIDER_TAG, "Put variable name:", chunk);
#endif
                refresh_assign_declaration_scope(spider, chunk, AIO_ASSIGN_WILL_DEFINED,
                                                 AIO_SPIDER_NOT_FOUND_MATERIALS);
                //Change scope:
                materials->scope_type = AIO_ASSIGN_EQUAL_SIGN_SCOPE;
            } else {
                //Not a variable name:
                //--------------------------------------------------------------------------------------------------
                //찌꺼기 수집기 (Garbage collector):
                free(chunk);
            }
        }
        if (materials->declaration_type == AIO_ASSIGN_WAS_MUTABLE_MODIFIER) {
#ifdef AIO_ASSIGN_SPIDER_DEBUG
            log_info(AIO_ASSIGN_SPIDER_TAG, "AIO_ASSIGN_WAS_MUTABLE_MODIFIER");
#endif
            //Maybe string is a type?
            if (is_type) {
#ifdef AIO_ASSIGN_SPIDER_DEBUG
                log_info_string(AIO_ASSIGN_SPIDER_TAG, "Put type:", chunk);
#endif
                refresh_assign_declaration_scope(spider, chunk, AIO_ASSIGN_MUTABLE,
                                                 AIO_SPIDER_NOT_FOUND_MATERIALS);
            }
            //Maybe string is a variable name?
            if (is_variable_name) {
#ifdef AIO_ASSIGN_SPIDER_DEBUG
                log_info_string(AIO_ASSIGN_SPIDER_TAG, "Put variable name:", chunk);
#endif
                refresh_assign_declaration_scope(spider, chunk, AIO_ASSIGN_REFERENCE,
                                                 AIO_SPIDER_NOT_FOUND_MATERIALS);
                //Change scope:
                materials->scope_type = AIO_ASSIGN_EQUAL_SIGN_SCOPE;
            } else {
                //Not a variable name:
                //--------------------------------------------------------------------------------------------------
                //찌꺼기 수집기 (Garbage collector):
                free(chunk);
            }
        }
        if (materials->declaration_type == AIO_ASSIGN_MUTABLE) {
#ifdef AIO_ASSIGN_SPIDER_DEBUG
            log_info(AIO_ASSIGN_SPIDER_TAG, "AIO_ASSIGN_MUTABLE");
#endif
            //Must be variable name:
            if (is_variable_name) {
#ifdef AIO_ASSIGN_SPIDER_DEBUG
                log_info_string(AIO_ASSIGN_SPIDER_TAG, "Put variable name:", chunk);
#endif
                refresh_assign_declaration_scope(spider, chunk, AIO_ASSIGN_MUTABLE, AIO_SPIDER_FOUND_MATERIALS);
                //Change scope:
                materials->scope_type = AIO_ASSIGN_EQUAL_SIGN_SCOPE;
            } else {
                throw_error_with_tag(AIO_ASSIGN_SPIDER_TAG, "Invalid variable name!");
            }
        }
    }
}

void refresh_assign_declaration_scope(aio_spider *spider, string chunk, aio_assign_variable_declaration_type type,
                                      aio_spider_message message) {
    //Extract materials:
    aio_assign_materials *materials = spider->get.assign_materials;
    string_list *variable_data_list = materials->variable_data_list;
    point_watcher *watcher = materials->main_watcher;
    //Change declaration type:
    materials->declaration_type = type;
    //Put chunk in list:
#ifdef AIO_ASSIGN_SPIDER_DEBUG
    log_info_string(AIO_ASSIGN_SPIDER_TAG, "PUT IN VARIABLE DATA LIST:", chunk);
#endif
    add_string_in_list(variable_data_list, chunk);
    //Shift main_watcher:
    watcher->start_index = watcher->end_index;
    watcher->mode = POINT_PASSIVE_MODE;
    //Set message:
    spider->message = message;
}

void handle_assign_equal_sign_scope(const_string string_web, aio_spider *spider) {
    aio_assign_materials *materials = spider->get.assign_materials;
    point_watcher *watcher = materials->main_watcher;
    const int start_scanning_index = watcher->end_index - 1;
    const_boolean is_equal_sign_symbol = is_equal_sign(string_web[start_scanning_index]);
    if (is_equal_sign_symbol) {
        //Set value scope:
        materials->scope_type = AIO_ASSIGN_VALUE_SCOPE;
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

void handle_assign_value_scope(const_string string_web, aio_spider *spider) {
    //Extract fields:
    aio_assign_materials *materials = spider->get.assign_materials;
    point_watcher *main_watcher = materials->main_watcher;
    point_watcher *value_watcher = materials->value_watcher;
    //Define last symbol:
    const int current_position = main_watcher->end_index - 1;
    const char current_symbol = string_web[current_position];
#ifdef AIO_ASSIGN_SPIDER_DEBUG
    log_info_int(AIO_ASSIGN_SPIDER_TAG, "CURRENT INDEX", main_watcher->end_index);
    log_info_int(AIO_ASSIGN_SPIDER_TAG, "LAST INDEX", materials->function_body_length);
    log_info_char(AIO_ASSIGN_SPIDER_TAG, "CURRENT SYMBOL:", current_symbol);
#endif
    //Check last symbol:
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    const_boolean is_close_parenthesis_cond = is_close_parenthesis(current_symbol);
    const_boolean is_letter_cond = isalpha(current_symbol);
    const_boolean is_letter_or_number_or_close_parenthesis_cond = isalnum(current_symbol) || is_close_parenthesis_cond;
    const_boolean is_last_function_body_position = materials->function_body_length - 1 == current_position;
    //Check value watcher conditions:
    if (is_letter_or_number_or_close_parenthesis_cond && value_watcher->mode == POINT_PASSIVE_MODE) {
        value_watcher->mode = POINT_ACTIVE_MODE;
        if (is_last_function_body_position) {
            value_watcher->end_index = main_watcher->end_index - value_watcher->pointer + 1;
            materials->scope_type = AIO_ASSIGN_WEAVING_SCOPE;
            materials->value = substring(string_web, main_watcher->start_index, value_watcher->end_index);
#ifdef AIO_ASSIGN_SPIDER_DEBUG
            log_info_string(AIO_ASSIGN_SPIDER_TAG, "VALUE:", materials->value);
#endif
            main_watcher->start_index = main_watcher->end_index;
            spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
        }
        return;
    }
    if (is_whitespace_cond && value_watcher->mode == POINT_ACTIVE_MODE) {
        value_watcher->pointer++;
        return;
    }
    if ((is_letter_cond) && value_watcher->mode == POINT_ACTIVE_MODE) {
        value_watcher->end_index = main_watcher->end_index - value_watcher->pointer - 1;
        materials->scope_type = AIO_ASSIGN_WEAVING_SCOPE;
        materials->value = substring(string_web, main_watcher->start_index, value_watcher->end_index);
#ifdef AIO_ASSIGN_SPIDER_DEBUG
        log_info_string(AIO_ASSIGN_SPIDER_TAG, "VALUE:", materials->value);
#endif

        main_watcher->start_index = main_watcher->end_index;
        spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
    } else {
        value_watcher->mode = POINT_PASSIVE_MODE;
        value_watcher->pointer = 0;
    }
}

/**
 * Instruction weaving.
 */

void weave_assign_instruction_for(aio_instruction_holder *holder, const_string _,
                                  int *next_ripper_point_reference, aio_spider *spider) {
    //Extract spider fields:
    const aio_assign_materials *materials = spider->get.assign_materials;
    const_string_array variable_data = materials->variable_data_list->strings;
    const_string value_string = materials->value;
    const point_watcher *watcher = materials->main_watcher;
    const aio_assign_variable_declaration_type declaration_type = materials->declaration_type;
    const_boolean is_ready_for_weaving = materials->scope_type == AIO_ASSIGN_WEAVING_SCOPE;
    if (is_ready_for_weaving) {
        *next_ripper_point_reference += watcher->end_index;
        //Weave variable definition:
        aio_variable_definition *new_definition = create_local_variable_definition(declaration_type, variable_data);
        const_string variable_name = new_definition->name;
        aio_variable_definition *definition = get_local_variable_definition_in_function_tree(variable_name, holder);
        if (definition == NULL) {
            definition = new_definition;
            //Put local definition in holder variable definition map:
            aio_variable_definition_map *map = holder->local_variable_definition_map;
            put_aio_variable_definition_in_map(map, definition);
        } else {
            if (!declaration_type == AIO_ASSIGN_WILL_DEFINED) {
                throw_error("ASSIGN SPIDER: variable already was defined in function tree!");
            }
            if (!definition->is_mutable_by_value) {
                throw_error("ASSIGN SPIDER: immutable variable can not change value!");
            }
            //----------------------------------------------------------------------------------------------------------
            //찌거기 수집기 (Garbage collector):
            free_aio_variable_definition(new_definition);
        }
        //Weave assign instruction:
        const_string assign_task_source = new_string(value_string);
        const_string assign_task_destination = new_string(variable_name);
        aio_instruction *assign_instruction = new_aio_assign_instruction(holder, assign_task_source,
                                                                         assign_task_destination);
        //Add assign instruction in holder's instructions:
        aio_instruction_list *instruction_list = holder->instruction_list;
        add_aio_instruction_in_list(instruction_list, assign_instruction);
        //Weaving complete!
    } else {
        throw_error("ASSIGN SPIDER: not ready for weaving!");
    }
}