#include <mem.h>
#include <ctype.h>
#include "../../../../../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../../../../headers/lib/point_watcher/point_watcher.h"
#include "../../../../../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"
#include "../../../../../../../../headers/lang/aio_core/aio_core.h"
#include "../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_spider/aio_spiders.h"
#include "../../../../../../../../headers/lib/utils/string_utils/string_builder.h"

#define AIO_ASSIGN_SPIDER_STATES 5

/**
 * Enum indices:
 */

#define AIO_SCOPE_INDEX 0

#define AIO_VARIABLE_DECLARATION_MODE_INDEX 1

/**
 * Scopes:
 */

const int AIO_VARIABLE_DECLARATION_SCOPE = 0;

const int AIO_EQUAL_SIGN_IN_SCOPE = 1;

const int AIO_ASSIGN_SCOPE = 2;

const int AIO_IS_WEAVING_SCOPE = 3;

/**
 * Variable declaration mode:
 */

const int AIO_UNDEFINED_DECLARATION = 0;

const int AIO_WAS_MUTABLE_MODIFIER = 1;

const int AIO_CONST_MODE = 2;

const int AIO_REFERENCE_MODE = 3;

const int AIO_IMMUTABLE_MODE = 4;

const int AIO_MUTABLE_BY_VALUE_MODE = 5;

/**
 * Material indices:
 */

const int AIO_VARIABLE_MATERIAL_INDEX = 0;

const AIO_ASSIGN_MATERIAL_INDEX = 2;


/**
 * Business logic:
 */

int *create_spider_protocol() {
    int *spider_protocol = calloc(AIO_ASSIGN_SPIDER_STATES, sizeof(int));
}

/**
 * Handlers:
 */

const_boolean handle_declaration_scope(string chunk,
                                       const int position,
                                       int *spider_protocol,
                                       int *spider_pointer_reference,
                                       spider_materials materials) {
    string_list *variable_material_list = materials[AIO_VARIABLE_MATERIAL_INDEX];
    const int variable_declaration_mode = spider_protocol[AIO_VARIABLE_DECLARATION_MODE_INDEX];
    const_boolean is_mutable_modifier = is_aio_mutable_modifier(chunk);
    const_boolean is_type = contains_aio_type_in_set(chunk);
    const_boolean is_variable_name = is_word(chunk) && can_use_name(chunk);
    switch (variable_declaration_mode) {
        //Undefined declaration:
        case 0:
            //Maybe string is the "mu" modifier?
            if (is_mutable_modifier) {
                spider_protocol[AIO_VARIABLE_DECLARATION_MODE_INDEX] = AIO_WAS_MUTABLE_MODIFIER;
                add_string_in_list(variable_material_list, chunk);
                return TRUE;
            }
            //Maybe string is a type?
            if (is_type) {
                spider_protocol[AIO_VARIABLE_DECLARATION_MODE_INDEX] = AIO_IMMUTABLE_MODE;
                add_string_in_list(variable_material_list, chunk);
                return TRUE;
            }
            //Maybe is a variable name?
            if (is_variable_name) {
                spider_protocol[AIO_VARIABLE_DECLARATION_MODE_INDEX] = AIO_CONST_MODE;
                *spider_protocol = AIO_EQUAL_SIGN_IN_SCOPE;
                *spider_pointer_reference = position;
                add_string_in_list(variable_material_list, chunk);
                return TRUE;
            } else {
                //Not a variable name:
                //------------------------------------------------------------------------------------------------------
                //찌꺼기 수집기 (Garbage collector):
                free(chunk);
                return FALSE;
            }
            //Was mutable modifier:
        case 1:
            //Maybe string is a type?
            if (is_type) {
                spider_protocol[AIO_VARIABLE_DECLARATION_MODE_INDEX] = AIO_MUTABLE_BY_VALUE_MODE;
                add_string_in_list(variable_material_list, chunk);
                return TRUE;
            }
            //Maybe string is a variable name?
            if (is_variable_name) {
                spider_protocol[AIO_VARIABLE_DECLARATION_MODE_INDEX] = AIO_REFERENCE_MODE;
                *spider_protocol = AIO_EQUAL_SIGN_IN_SCOPE;
                *spider_pointer_reference = position;
                add_string_in_list(variable_material_list, chunk);
                return TRUE;
            } else {
                //Not a variable name:
                //------------------------------------------------------------------------------------------------------
                //찌꺼기 수집기 (Garbage collector):
                free(chunk);
                return FALSE;
            }
            //Mutable by value mode:
        case 5:
            //Must be variable name:
            if (is_word(chunk)) {
                *spider_protocol = AIO_EQUAL_SIGN_IN_SCOPE;
                *spider_pointer_reference = position;
                return TRUE;
            } else {
                //Not a variable name:
                //------------------------------------------------------------------------------------------------------
                //찌꺼기 수집기 (Garbage collector):
                free(chunk);
                return FALSE;
            }
        default:
            throw_error("ASSIGN SPIDER: Unreachable case!");
    }
}

const_boolean handle_equal_sign_scope(string chunk,
                                      const int position,
                                      int *spider_protocol,
                                      int *spider_pointer_reference) {
    const_boolean is_equal_sign_symbol = is_equal_sign(chunk[0]);
    if (is_equal_sign_symbol) {
        *spider_protocol = AIO_ASSIGN_SCOPE;
        *spider_pointer_reference = position;
    } else {
        //Not a equal sign:
        //----------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free(chunk);
        return FALSE;
    }
}

const_boolean handle_assign_scope(string chunk,
                                  int *spider_protocol,
                                  int *spider_pointer_reference,
                                  spider_materials materials) {
    string_list *assign_material_list = materials[AIO_ASSIGN_MATERIAL_INDEX];
    const size_t chunk_length = strlen(chunk);
    const int last_position = chunk_length - 1;
    const char last_symbol = chunk[last_position];
    //Try to find regex:
    int space_or_line_break_counter = 0;
    if (isalnum(last_symbol) && chunk_length >= 3) {
        for (int i = last_position - 1; i > 0; --i) {
            const char symbol = chunk[i];
            const_boolean is_space_or_line_break_condition = is_space_or_line_break(symbol);
            if (is_space_or_line_break_condition) {
                space_or_line_break_counter++;
            }
            if (!is_space_or_line_break_condition && space_or_line_break_counter == 0) {
                if (isalnum(symbol)) {
                    *spider_pointer_reference -= space_or_line_break_counter;
                    spider_protocol[AIO_SCOPE_INDEX] = AIO_IS_WEAVING_SCOPE;
                    string variable_or_expression = substring(chunk, 0, chunk_length - space_or_line_break_counter);
                    add_string_in_list(assign_material_list, variable_or_expression);
                    return TRUE;
                } else {
                    return FALSE;
                }
            }
        }
    }
}

/**
 *
 * @param string_web
 * @param spider_pointer_reference
 * @param spider_protocol
 * @param materials
 * @return
 */

const_boolean is_found_assign_instruction(const_string string_web,
                                          int *spider_pointer_reference,
                                          int *spider_protocol,
                                          spider_materials materials) {
    const int start_point = *spider_pointer_reference;
    const size_t string_web_length = strlen(string_web);
    point_watcher *watcher = new_point_watcher();
    string_builder *str_builder = new_string_builder();
    for (int i = start_point; i < string_web_length; ++i) {
        const char symbol = string_web[i];
        const_boolean is_space_or_line_break_condition = is_space_or_line_break(symbol);
        const_boolean is_assign_scope = spider_protocol[AIO_SCOPE_INDEX] == AIO_ASSIGN_SCOPE;
        //Start read word:
        if (!is_space_or_line_break_condition && watcher->mode == POINT_PASSIVE_MODE) {
            if (!is_assign_scope) {
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
                //Declaration scope:
                case 0: {
                    const_boolean is_changed_state = handle_declaration_scope(chunk, i, spider_protocol,
                                                                              spider_pointer_reference, materials);
                    if (!is_changed_state) {
                        return FALSE;
                    }
                }
                    break;
                    //--------------------------------------------------------------------------------------------------
                    //Equal sign scope:
                case 1: {
                    const_boolean is_changed_state = handle_equal_sign_scope(chunk, i, spider_protocol,
                                                                             spider_pointer_reference);
                    watcher->mode = POINT_PASSIVE_MODE;
                    if (!is_changed_state) {
                        return FALSE;
                    }
                }
                    break;
                default:
                    break;
            }
        }
        //--------------------------------------------------------------------------------------------------------------
        //Assign scope:
        if (spider_protocol[AIO_SCOPE_INDEX] == AIO_ASSIGN_SCOPE && watcher->mode == POINT_UNDEFINED_MODE) {
            append_char(str_builder, symbol);
            string chunk = str_builder->string_value;
            const_boolean is_ready_for_weaving
                    = handle_assign_scope(chunk, spider_protocol, spider_pointer_reference, materials);
            return is_ready_for_weaving;
        }
    }
    return FALSE;
}

/**
 * Weaving.
 */

/**
 *
 * @param variable_declaration_mode
 * @param variable_materials
 * @return
 */


aio_variable_definition *weave_local_definition(const int variable_declaration_mode,
                                                const_string_array variable_materials) {
    string variable_name = NULL;
    string variable_type = NULL;
    boolean is_mutable = FALSE;
    switch (variable_declaration_mode) {
        //Const mode:
        case 2:
            variable_name = new_string(variable_materials[0]);
            variable_type = AIO_CONST_TYPE;
            is_mutable = FALSE;
            break;
            //Reference mode:
        case 3:
            variable_name = new_string(variable_materials[1]);
            variable_type = VOID;
            is_mutable = TRUE;
            break;
            //Immutable mode:
        case 4:
            variable_name = new_string(variable_materials[1]);
            variable_type = new_string(variable_materials[0]);
            is_mutable = FALSE;
            break;
            //Mutable by value mode:
        case 5:
            variable_name = new_string(variable_materials[1]);
            variable_type = new_string(variable_materials[0]);
            is_mutable = TRUE;
            break;
        default:
            throw_error("ASSIGN SPIDER: undefined variable declaration mode for weaving!");
    }
    aio_variable_definition *definition = new_aio_variable_definition(variable_name, variable_type, is_mutable);
    return definition;
}

void weave_assign_instruction_for(
        aio_instruction_holder *instruction_holder,
        int *function_body_next_start_position_reference,
        int *spider_pointer_reference,
        int *spider_protocol,
        spider_materials materials) {
    *function_body_next_start_position_reference += *spider_pointer_reference;
    const_boolean is_ready_for_weaving = spider_protocol[AIO_SCOPE_INDEX] == AIO_IS_WEAVING_SCOPE;
    if (is_ready_for_weaving) {
        //Get spider's materials:
        const_string_array variable_materials = materials[AIO_VARIABLE_MATERIAL_INDEX]->strings;
        const_string_array assign_materials = materials[AIO_ASSIGN_MATERIAL_INDEX]->strings;
        //Weave instruction:
        aio_instruction *instruction;
        //Weave variable definition:
        const int variable_declaration_mode = spider_protocol[AIO_VARIABLE_DECLARATION_MODE_INDEX];
        aio_variable_definition *definition = weave_local_definition(variable_declaration_mode, variable_materials);
        //Put local definition in holder variable definition map:
        aio_variable_definition_map* map = instruction_holder->local_variable_definition_map;
        put_aio_variable_definition_in_map(map, definition);
        //Weave assign instruction:
        const_string variable_name = definition->name;
        const_string assign_task_source = new_string(assign_materials[0]);
        const_string assign_task_destination = new_string(variable_name);
        aio_instruction *assign_instruction = new_aio_assign_instruction(instruction_holder, assign_task_source
                , assign_task_destination);
        //Add assign instruction in holder's instructions:
        aio_instruction_list* instruction_list = instruction_holder->instruction_list;
        add_aio_instruction_in_list(instruction_list, assign_instruction);
        //Weaving complete!
    } else {
        throw_error("ASSIGN SPIDER: not ready for weaving!");
    }
}