#include <mem.h>
#include <ctype.h>
#include "../../../../../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../../../../headers/lib/point_watcher/point_watcher.h"
#include "../../../../../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"
#include "../../../../../../../../headers/lang/aio_core/aio_core.h"

#define AIO_ASSIGN_SPIDER_STATES 5

/**
 * Enum indices:
 */

#define AIO_WATCHING_SCOPE_INDEX 0

#define AIO_VARIABLE_DECLARATION_MODE 1

/**
 * Watching scopes:
 */

const int AIO_VARIABLE_DECLARATION_SCOPE = 0;

const int AIO_EQUAL_SIGN_IN_SCOPE = 1;

const int AIO_ASSIGN_SCOPE = 2;

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
 * Business logic:
 */

int *create_spider_states() {
    int *spider_states = calloc(AIO_ASSIGN_SPIDER_STATES, sizeof(int));
}

const_boolean is_found_assign_instruction(const_string string_web, int *spider_pointer_reference, int *spider_states) {
    const int start_point = *spider_pointer_reference;
    const size_t string_web_length = strlen(string_web);
    point_watcher *watcher = new_point_watcher();
    for (int i = start_point; i < string_web_length; ++i) {
        const char symbol = string_web[i];
        const_boolean is_space_or_line_break_condition = is_space_or_line_break(symbol);
        //Start read word:
        if (!is_space_or_line_break_condition && watcher->mode == POINT_UNDEFINED) {
            watcher->mode = POINT_WATCHING_MODE;
            watcher->start_index = i;
        }
        //End read word:
        if (is_space_or_line_break_condition && watcher->mode == POINT_WATCHING_MODE) {
            //Turn off watcher:
            watcher->mode = POINT_UNDEFINED;
            watcher->end_index = i;
            //Extract first string:
            const_string chunk = substring(string_web, watcher->start_index, watcher->end_index);
            //Watching scopes:
            switch (spider_states[AIO_WATCHING_SCOPE_INDEX]) {
                //------------------------------------------------------------------------------------------------------
                //Declaration scope:
                case 0:
                    switch (spider_states[AIO_VARIABLE_DECLARATION_MODE]) {
                        //Undefined declaration:
                        case 0:
                            //Maybe string is the "mu" modifier?
                            if (is_aio_mutable_modifier(chunk)) {
                                spider_states[AIO_VARIABLE_DECLARATION_MODE] = AIO_WAS_MUTABLE_MODIFIER;
                            } else
                                //Maybe string is a type?
                            if (contains_aio_type_in_set(chunk)) {
                                spider_states[AIO_VARIABLE_DECLARATION_MODE] = AIO_IMMUTABLE_MODE;
                            } else
                                //Maybe is a variable name?
                            if (is_word(chunk)) {
                                spider_states[AIO_VARIABLE_DECLARATION_MODE] = AIO_CONST_MODE;
                                *spider_states = AIO_EQUAL_SIGN_IN_SCOPE;
                            } else {
                                //Not a variable name:
                                return FALSE;
                            }
                            break;
                            //Was mutable modifier:
                        case 1:
                            //Maybe string is a type?
                            if (contains_aio_type_in_set(chunk)) {
                                spider_states[AIO_VARIABLE_DECLARATION_MODE] = AIO_MUTABLE_BY_VALUE_MODE;
                            } else
                                //Maybe string is a variable name?
                            if (is_word(chunk)) {
                                spider_states[AIO_VARIABLE_DECLARATION_MODE] = AIO_REFERENCE_MODE;
                                *spider_states = AIO_EQUAL_SIGN_IN_SCOPE;
                            } else {
                                //Not a variable name:
                                return FALSE;
                            }
                            break;
                            //Mutable by value mode:
                        case 5:
                            //Must be variable name:
                            if (is_word(chunk)) {
                                *spider_states = AIO_EQUAL_SIGN_IN_SCOPE;
                            } else {
                                //Not a variable name:
                                return FALSE;
                            }
                            break;
                        default:
                            throw_error("ASSIGN SPIDER: Unreachable case!");
                    }
                    break;
                    //--------------------------------------------------------------------------------------------------
                    //Equal sign scope:
                case 1:
                    if (is_equal_sign(chunk[0])) {
                        *spider_states = AIO_ASSIGN_SCOPE;
                    } else {
                        return FALSE;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return FALSE;
}

void weave_assign_instruction_for(aio_instruction_holder *instruction_holder, const_string string_web, int *pointer) {

}