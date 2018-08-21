#include <malloc.h>
#include <ctype.h>
#include <mem.h>
#include "../../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"
#include "../../../../../../headers/lang/aio_core/aio_core.h"
#include "../../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../../headers/lang/aio_function/aio_variable/aio_definition/aio_variable_definition.h"
#include "../../../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"
#include "../../../../../../headers/lang/aio_type/aio_type.h"
#include "../../../../../../headers/tools/aio_common_tools/aio_spider_nest/aio_spider.h"
#include "../../../../../../headers/tools/aio_function_tools/aio_instruction_spider_nest/aio_loop_spider/aio_loop_spider.h"

/**
 * Business logic.
 */

#define AIO_DEFAULT_LOOP_HEADER_SPIDER_DEBUG

#define AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG "AIO_DEFAULT_LOOP_HEADER_SPIDER"

#ifdef AIO_DEFAULT_LOOP_HEADER_SPIDER_DEBUG

#include "../../../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

/**
 * Refresh.
 */

static void refresh_default_loop_header_materials(aio_default_loop_header_materials *materials,
                                                  point_watcher *parent_watcher) {
    //Reset states:
    materials->scope_type = AIO_DEFAULT_LOOP_HEADER_DECLARATION_SCOPE;
    materials->declaration_type = AIO_DEFAULT_LOOP_HEADER_VARIABLE_UNDEFINED;
    materials->step_type = AIO_DEFAULT_LOOP_HEADER_STEP_VARIABLE;
    //Refresh main watcher:
    materials->main_watcher->start = parent_watcher->pointer;
    materials->main_watcher->end = parent_watcher->pointer;
    materials->main_watcher->mode = POINT_PASSIVE_MODE;
    reset_point_watcher(materials->value_watcher);
    reset_point_watcher(materials->condition_watcher);
    //Reset data:
    const_str_hook_list *old_pointer_data_list = materials->pointer_data_list;
    string old_init_value = materials->init_value;
    string old_loop_condition = materials->loop_condition;
    string old_step_value = materials->step_value;
    materials->pointer_data_list = new_str_hook_list();
    materials->init_value = NULL;
    materials->loop_condition = NULL;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_str_hooks_in_list(old_pointer_data_list);
    free_str_hook_list(old_pointer_data_list);
    free(old_init_value);
    free(old_loop_condition);
    free(old_step_value);
}

static void refresh_default_loop_header_spider(aio_spider *spider, point_watcher *parent_watcher) {
    //Set message:
    aio_default_loop_header_materials *materials = spider->materials;
    refresh_default_loop_header_materials(materials, parent_watcher);
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
}

/**
 * Free spider.
 */

static void free_default_loop_header_materials(aio_default_loop_header_materials *materials) {
    //Free watchers:
    free_point_watcher(materials->main_watcher);
    free_point_watcher(materials->condition_watcher);
    free_point_watcher(materials->value_watcher);
    //Reset data:
    free_str_hooks_in_list(materials->pointer_data_list);
    free_str_hook_list(materials->pointer_data_list);
    free(materials->init_value);
    free(materials->loop_condition);
    free(materials->step_value);
    free(materials);
}

static void free_default_loop_header_spider(aio_spider *spider) {
    aio_default_loop_header_materials *materials = spider->materials;
    free_default_loop_header_materials(materials);
    //Free spider:
    free(spider);
}

/**
 * Searching.
 */

static void refresh_default_loop_header_declaration_scope(aio_spider *spider, const_str_hook *hook,
                                                   aio_default_loop_header_pointer_declaration_type type,
                                                   aio_spider_message message) {
    //Extract materials:
    aio_default_loop_header_materials *materials = spider->materials;
    str_hook_list *variable_data_list = materials->pointer_data_list;
    point_watcher *watcher = materials->main_watcher;
    //Change declaration type:
    materials->declaration_type = type;
#ifdef AIO_DEFAULT_LOOP_HEADER_SPIDER_DEBUG
    log_info_str_hook(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, ">>>We-e-e-a-ved!!!>>>", hook);
#endif
    add_str_hook_in_list(variable_data_list, hook);
#ifdef AIO_DEFAULT_LOOP_HEADER_SPIDER_DEBUG
    log_info_str_hook(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, ">>>", hook);
#endif
    //Shift main_watcher:
    watcher->start = watcher->end + 1;
    watcher->mode = POINT_PASSIVE_MODE;
    //Set message:
    spider->message = message;
}

static void handle_default_loop_header_declaration_scope(const_string string_web, aio_spider *spider) {
    //Extract materials:
    aio_default_loop_header_materials *materials = spider->materials;
    point_watcher *main_watcher = materials->main_watcher;
    //Check string web:
    const char current_symbol = string_web[main_watcher->end];
    //Check current symbol:
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    const_boolean is_equal_sign_cond = is_equal_sign(current_symbol);
    if (is_whitespace_cond || is_equal_sign_cond) {
        const_str_hook *hook = new_str_hook_by_point_watcher(string_web, main_watcher);
#ifdef AIO_DEFAULT_LOOP_HEADER_SPIDER_DEBUG
        log_info_str_hook(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, "CAPTURED CHUNK", hook);
#endif
        //Check conditions:
        const_boolean is_mutable_modifier = is_aio_mutable_modifier(hook);
        const_boolean is_type = is_aio_type_hooked(hook);
        const_boolean is_variable_name = is_word_hooked(hook) && can_use_name(hook);
        if (materials->declaration_type == AIO_DEFAULT_LOOP_HEADER_VARIABLE_UNDEFINED) {
            //Maybe string is the "mu" modifier?
            if (is_mutable_modifier) {
                refresh_default_loop_header_declaration_scope(spider, hook,
                                                              AIO_DEFAULT_LOOP_HEADER_WAS_MUTABLE_MODIFIER,
                                                              AIO_SPIDER_FOUND_MATERIALS);
                return;
            }
            //Maybe string is a type?
            if (is_type) {
#ifdef AIO_DEFAULT_LOOP_HEADER_SPIDER_DEBUG
                log_info_str_hook(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, "FOUND TYPE!", hook);
#endif
                refresh_default_loop_header_declaration_scope(spider, hook, AIO_DEFAULT_LOOP_HEADER_IMMUTABLE,
                                                              AIO_SPIDER_FOUND_MATERIALS);
                return;
            } else {
                //Maybe start of loop condition?
                //Hasn't variable:
                materials->declaration_type = AIO_DEFAULT_LOOP_HEADER_ABSENT;
                main_watcher->mode = POINT_UNDEFINED_MODE;
                //Change scope:
                materials->scope_type = AIO_DEFAULT_LOOP_HEADER_CONDITION_SCOPE;
                //--------------------------------------------------------------------------------------------------
                //찌꺼기 수집기 (Garbage collector):
                free_const_str_hook(hook);
            }
        }
        if (materials->declaration_type == AIO_DEFAULT_LOOP_HEADER_WAS_MUTABLE_MODIFIER) {
            //Maybe string is a type?
            if (is_type) {
                refresh_default_loop_header_declaration_scope(spider, hook, AIO_DEFAULT_LOOP_HEADER_MUTABLE,
                                                              AIO_SPIDER_FOUND_MATERIALS);
                return;
            }
            //Maybe string is a variable name?
            if (is_variable_name) {
                refresh_default_loop_header_declaration_scope(spider, hook, AIO_DEFAULT_LOOP_HEADER_REFERENCE,
                                                              AIO_SPIDER_FOUND_MATERIALS);
                //Change scope:
                materials->scope_type = AIO_DEFAULT_LOOP_HEADER_EQUAL_SIGN_SCOPE;
            } else {
                //Not a variable name:
                throw_error_with_tag(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG,
                                     "Invalid type or variable name in loop header!");
            }
        }
        if (materials->declaration_type == AIO_DEFAULT_LOOP_HEADER_IMMUTABLE
            || materials->declaration_type == AIO_DEFAULT_LOOP_HEADER_MUTABLE) {
            //Must be variable name:
            if (is_variable_name) {
                refresh_default_loop_header_declaration_scope(spider, hook, materials->declaration_type,
                                                              AIO_SPIDER_FOUND_MATERIALS);
                //Change scope:
                materials->scope_type = AIO_DEFAULT_LOOP_HEADER_EQUAL_SIGN_SCOPE;
            } else {
                throw_error_with_tag(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, "Invalid variable name in loop header!");
            }
        }
    }
}

static void handle_default_loop_header_equal_sign_scope(const_string source_code, aio_spider *spider) {
    aio_default_loop_header_materials *materials = spider->materials;
    point_watcher *main_watcher = materials->main_watcher;
    const char current_symbol = source_code[main_watcher->end];
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    const_boolean is_equal_sign_cond = is_equal_sign(current_symbol);
    if (is_whitespace_cond) {
        return;
    }
    if (is_equal_sign_cond) {
        //Set value scope:
        materials->scope_type = AIO_DEFAULT_LOOP_HEADER_VALUE_SCOPE;
        //Shift start index from end index:
        main_watcher->start = main_watcher->end + 1;
        main_watcher->mode = POINT_PASSIVE_MODE;
        //Set message:
        spider->message = AIO_SPIDER_FOUND_MATERIALS;
#ifdef AIO_DEFAULT_LOOP_HEADER_SPIDER_DEBUG
        log_info(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, "Equal sign is fo-o-o-und!");
#endif
    } else {
        if (spider->message == AIO_SPIDER_FOUND_MATERIALS) {
            throw_error_with_tag(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG,
                                 "Waiting for equal sign! Invalid variable definition!");
        }
    }
}

static void handle_default_loop_header_value_scope(const_string source_code, aio_spider *spider) {
    //재료들을 추출하다 (Extract materials):
    aio_default_loop_header_materials *materials = spider->materials;
    point_watcher *main_watcher = materials->main_watcher;
    point_watcher *value_watcher = materials->value_watcher;
    const int current_position = main_watcher->end;
    const char current_symbol = source_code[current_position];
    //Check current symbol:
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    const_boolean is_close_parenthesis_cond = is_closing_parenthesis(current_symbol);
    const_boolean is_letter_or_number_cond = isalnum(current_symbol);
    const_boolean is_letter_or_number_or_close_parenthesis_cond = is_letter_or_number_cond || is_close_parenthesis_cond;
    if (is_whitespace_cond && value_watcher->mode == POINT_ACTIVE_MODE) {
        value_watcher->pointer++;
        return;
    }
    if (is_letter_or_number_cond && value_watcher->mode == POINT_ACTIVE_MODE && value_watcher->pointer > 0) {
        value_watcher->start = main_watcher->start;
        value_watcher->end = main_watcher->end - value_watcher->pointer;
        //값을 놓다 (Set value):
        string dirty_value = substring_by_point_watcher(source_code, value_watcher);
        string clean_value = squeeze_string(dirty_value);
        materials->init_value = clean_value;
        //위빙 준비 (Prepare for weaving):
        materials->scope_type = AIO_DEFAULT_LOOP_HEADER_CONDITION_SCOPE;
        main_watcher->start = main_watcher->end;
#ifdef AIO_DEFAULT_LOOP_HEADER_SPIDER_DEBUG
        log_info_string(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, "CAPTURED VALUE:", clean_value);
#endif
        //--------------------------------------------------------------------------------------------------------------
        //찌거기 수집기 (Garbage collector):
        free((void *) dirty_value);
    } else {
        value_watcher->mode = POINT_PASSIVE_MODE;
        value_watcher->pointer = 0;
        if (is_letter_or_number_or_close_parenthesis_cond && value_watcher->mode == POINT_PASSIVE_MODE) {
            value_watcher->mode = POINT_ACTIVE_MODE;
            return;
        }
    }
}

static void handle_default_loop_header_condition_scope(const_string source_code, point_watcher *parent_watcher,
                                                aio_spider *spider) {
    //Extract materials:
    aio_default_loop_header_materials *materials = spider->materials;
    const aio_default_loop_header_pointer_declaration_type declaration_type = materials->declaration_type;
    point_watcher *main_watcher = materials->main_watcher;
    //Check string web:
    const int current_position = main_watcher->end;
    const char current_symbol = source_code[current_position];
    //Check symbol:
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    const_boolean is_close_parenthesis_cond = is_closing_parenthesis(current_symbol);
    const_boolean is_letter_cond = isalpha(current_symbol);
    const_boolean is_letter_or_number_or_close_parenthesis_cond = isalnum(current_symbol) || is_close_parenthesis_cond;
    //Check declaration_type:
    const_boolean is_not_step_assign_in_header = declaration_type == AIO_DEFAULT_LOOP_HEADER_ABSENT
                                                 || declaration_type == AIO_DEFAULT_LOOP_HEADER_MUTABLE
                                                 || declaration_type == AIO_DEFAULT_LOOP_HEADER_REFERENCE;
    if (is_not_step_assign_in_header) {
        const_string dirty_loop_condition = substring(source_code, main_watcher->start, parent_watcher->end - 1);
        string clean_loop_condition = squeeze_string(dirty_loop_condition);
        materials->loop_condition = clean_loop_condition;
        materials->scope_type = AIO_DEFAULT_LOOP_HEADER_WEAVING_SCOPE;
        spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free((void *) dirty_loop_condition);
#ifdef AIO_DEFAULT_LOOP_HEADER_SPIDER_DEBUG
        log_info_string(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, "CAPTURED CONDITION WITHOUT POINTER:",
                        clean_loop_condition);
#endif
    } else {
        point_watcher *condition_watcher = materials->condition_watcher;
        if (is_whitespace_cond && condition_watcher->mode == POINT_ACTIVE_MODE) {
            condition_watcher->pointer++;
            return;
        }
        if (is_letter_cond && condition_watcher->mode == POINT_ACTIVE_MODE && condition_watcher->pointer > 0) {
            condition_watcher->start = main_watcher->start;
            condition_watcher->end = main_watcher->end - condition_watcher->pointer;
            //값을 놓다 (Set value):
            string dirty_loop_condition = substring_by_point_watcher(source_code, condition_watcher);
            string clean_loop_condition = squeeze_string(dirty_loop_condition);
            materials->loop_condition = clean_loop_condition;
            //위빙 준비 (Prepare for weaving):
            materials->scope_type = AIO_DEFAULT_LOOP_HEADER_STEP_SCOPE;
            main_watcher->start = main_watcher->end;
#ifdef AIO_DEFAULT_LOOP_HEADER_SPIDER_DEBUG
            log_info_string(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, "CAPTURED CONDITION WITH POINTER:",
                            clean_loop_condition);
#endif
            //----------------------------------------------------------------------------------------------------------
            //찌거기 수집기 (Garbage collector):
            free(dirty_loop_condition);
        } else {
            condition_watcher->mode = POINT_PASSIVE_MODE;
            condition_watcher->pointer = 0;
            if (is_letter_or_number_or_close_parenthesis_cond && condition_watcher->mode == POINT_PASSIVE_MODE) {
                condition_watcher->mode = POINT_ACTIVE_MODE;
                return;
            }
        }
    }
}

const_str_hook *get_default_loop_pointer_name_by_materials(const aio_default_loop_header_materials *materials) {
    const_str_hook_array pointer_data = materials->pointer_data_list->hooks;
    const aio_default_loop_header_pointer_declaration_type declaration_type = materials->declaration_type;
    const_str_hook *pointer_name = NULL;
    if (declaration_type == AIO_DEFAULT_LOOP_HEADER_MUTABLE) {
        pointer_name = pointer_data[2];
    }
    if (declaration_type == AIO_DEFAULT_LOOP_HEADER_IMMUTABLE
        || declaration_type == AIO_DEFAULT_LOOP_HEADER_REFERENCE) {
        pointer_name = pointer_data[1];
    }
    return pointer_name;
}

static const_boolean is_same_default_loop_pointer(const_str_hook *input_name, aio_default_loop_header_materials *materials) {
    const_str_hook *pointer_name = get_default_loop_pointer_name_by_materials(materials);
    return are_equal_hooked_str(pointer_name, input_name);
}

static void handle_default_loop_header_step_scope(const_string source_code, point_watcher *parent_watcher,
                                           aio_spider *spider) {
    //Extract materials:
    aio_default_loop_header_materials *materials = spider->materials;
    point_watcher *main_watcher = materials->main_watcher;
    //Check string web:
    const char current_symbol = source_code[main_watcher->end];
#ifdef AIO_DEFAULT_LOOP_HEADER_SPIDER_DEBUG
    log_info_char(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, "CURRENT SYMBOL:", current_symbol);
#endif
    //Check current symbol:
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    const_boolean is_equal_sign_cond = is_equal_sign(current_symbol);
    if (is_whitespace_cond || is_equal_sign_cond) {
        const_str_hook *hook = new_str_hook_by_point_watcher(source_code, main_watcher);
        if (materials->step_type == AIO_DEFAULT_LOOP_HEADER_STEP_VARIABLE) {
            //Must be variable name:
            if (is_word_hooked(hook) && can_use_name(hook) && is_same_default_loop_pointer(hook, materials)) {
                //Change declaration type:
                materials->step_type = AIO_DEFAULT_LOOP_HEADER_STEP_EQUAL_SIGN_SCOPE;
                //Shift main_watcher:
                main_watcher->start = main_watcher->end;
                main_watcher->mode = POINT_PASSIVE_MODE;
                //Set message:
                spider->message = AIO_SPIDER_FOUND_MATERIALS;
#ifdef AIO_DEFAULT_LOOP_HEADER_SPIDER_DEBUG
                log_info_str_hook(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, "CAPTURED POINTER:", hook);
#endif
            } else {
                throw_error_with_tag(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, "Invalid variable name in loop header step !");
            }
        }
        if (materials->step_type == AIO_DEFAULT_LOOP_HEADER_STEP_EQUAL_SIGN_SCOPE) {
            if (is_whitespace_cond) {
                return;
            }
            if (is_equal_sign_cond) {
                //Set value scope:
                materials->step_type = AIO_DEFAULT_LOOP_HEADER_STEP_VALUE_SCOPE;
                //Shift start index from end index:
                main_watcher->start = main_watcher->end;
                main_watcher->mode = POINT_PASSIVE_MODE;
                //Set message:
                spider->message = AIO_SPIDER_FOUND_MATERIALS;
#ifdef AIO_DEFAULT_LOOP_HEADER_SPIDER_DEBUG
                log_info(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, "FOUND EQUAL SIGN IN STEP!!!.........");
#endif
                return;
            } else {
                throw_error_with_tag(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, "Waiting equal sign in step scope!");
            }
        }
    }
    if (materials->step_type == AIO_DEFAULT_LOOP_HEADER_STEP_VALUE_SCOPE) {
        //Get rest:
        const int start_index = main_watcher->start;
        //Don't hold closing parenthesis:
        const int end_index = parent_watcher->end - 1;
        string dirty_step_value = substring(source_code, start_index, end_index);
        string clean_step_value = squeeze_string(dirty_step_value);
        materials->step_value = clean_step_value;
        materials->scope_type = AIO_DEFAULT_LOOP_HEADER_WEAVING_SCOPE;
        spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
        //----------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free(dirty_step_value);
#ifdef AIO_DEFAULT_LOOP_HEADER_SPIDER_DEBUG
        log_info_string(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, "CAPTURED STEP VALUE:", clean_step_value);
#endif
    }
}

static const aio_spider_message is_found_default_loop_header_instruction(const_string source_code,
                                                                  point_watcher *parent_watcher, aio_spider *spider) {
    //Extract spider fields:
    const aio_default_loop_header_materials *materials = spider->materials;
    point_watcher *main_watcher = materials->main_watcher;
    main_watcher->end = parent_watcher->pointer;
    //Define current symbol:
    const char current_symbol = source_code[main_watcher->end];
    //Check symbol:
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    if (main_watcher->mode == POINT_PASSIVE_MODE) {
        if (is_whitespace_cond) {
            main_watcher->start++;
        } else {
            main_watcher->mode = POINT_ACTIVE_MODE;
        }
    }
    if (main_watcher->mode == POINT_ACTIVE_MODE) {
        if (materials->scope_type == AIO_DEFAULT_LOOP_HEADER_DECLARATION_SCOPE) {
            handle_default_loop_header_declaration_scope(source_code, spider);
        }
        if (materials->scope_type == AIO_DEFAULT_LOOP_HEADER_EQUAL_SIGN_SCOPE) {
            handle_default_loop_header_equal_sign_scope(source_code, spider);
            return spider->message;
        }
        if (materials->scope_type == AIO_DEFAULT_LOOP_HEADER_VALUE_SCOPE) {
            handle_default_loop_header_value_scope(source_code, spider);
        }
        if (materials->scope_type == AIO_DEFAULT_LOOP_HEADER_CONDITION_SCOPE) {
            handle_default_loop_header_condition_scope(source_code, parent_watcher, spider);
        }
        if (materials->scope_type == AIO_DEFAULT_LOOP_HEADER_STEP_SCOPE) {
            handle_default_loop_header_step_scope(source_code, parent_watcher, spider);
        }
    }
    return spider->message;
}

/**
 * Extra handlers:
 */

static void weave_default_loop_materials_for(void *parent, const_string _, struct point_watcher *header_watcher,
                                      struct aio_spider *spider) {
    aio_spider *loop_spider = parent;
    header_watcher->pointer = header_watcher->end;
    aio_loop_materials *dst_materials = loop_spider->materials;
    aio_default_loop_header_materials *src_materials = spider->materials;
    const_str_hook_list *src_pointer_list = src_materials->pointer_data_list;
    aio_default_loop_header_materials *new_materials = new_object(sizeof(aio_default_loop_header_materials));
    new_materials->declaration_type = src_materials->declaration_type;
#ifdef AIO_DEFAULT_LOOP_HEADER_SPIDER_DEBUG
    log_info_string(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, "START STEP VALUE", src_materials->step_value);
#endif
    new_materials->step_value = new_string(src_materials->step_value);
#ifdef AIO_DEFAULT_LOOP_HEADER_SPIDER_DEBUG
    log_info(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, "START WEAVING!!!!");
#endif
    new_materials->loop_condition = new_string(src_materials->loop_condition);
    new_materials->init_value = new_string(src_materials->init_value);
    str_hook_list *new_pointer_list = new_str_hook_list();
    for (int i = 0; i < src_pointer_list->size; ++i) {
        add_str_hook_in_list(new_pointer_list, new_str_hook_by_other(src_pointer_list->hooks[i]));
    }
    new_materials->pointer_data_list = new_pointer_list;
    dst_materials->get_applied_materials_from.default_loop_header = new_materials;
    dst_materials->applied_header_material_type = AIO_LOOP_MATERIALS_DEFAULT_HEADER;
#ifdef AIO_DEFAULT_LOOP_HEADER_SPIDER_DEBUG
    log_info(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, "Weaving is complete!");
#endif
}

aio_variable_definition *create_pointer_variable_definition_by_default_loop_header_spider(
        const aio_default_loop_header_pointer_declaration_type declaration_type, const_str_hook_array pointer_data) {
    const_str_hook *pointer_name = NULL;
    str_hook *pointer_type = NULL;
    boolean is_mutable_pointer = FALSE;
    if (declaration_type == AIO_DEFAULT_LOOP_HEADER_MUTABLE) {
        pointer_name = new_str_hook_by_other(pointer_data[2]);
        pointer_type = new_str_hook_by_other(pointer_data[1]);
        is_mutable_pointer = TRUE;
    }
    if (declaration_type == AIO_DEFAULT_LOOP_HEADER_IMMUTABLE) {
        pointer_name = new_str_hook_by_other(pointer_data[1]);
        pointer_type = new_str_hook_by_other(pointer_data[0]);
    }
    if (declaration_type == AIO_DEFAULT_LOOP_HEADER_REFERENCE) {
        pointer_name = new_str_hook_by_other(pointer_data[1]);
        pointer_type = new_str_hook_by_string(VOID);
        is_mutable_pointer = TRUE;
    }
    return new_aio_variable_definition(pointer_name, pointer_type, is_mutable_pointer);
}

/**
 * Constructor.
 */

struct aio_spider *new_aio_default_loop_header_spider(point_watcher *parent_watcher) {
#ifdef AIO_DEFAULT_LOOP_HEADER_SPIDER_DEBUG
    log_info(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, "Start to create spider...");
#endif
    aio_spider *spider = new_object(sizeof(aio_spider));
    //함수들을 놓다 (Put functions):
    spider->refresh = refresh_default_loop_header_spider;
    spider->is_found_context = is_found_default_loop_header_instruction;
    spider->weave_context_for = weave_default_loop_materials_for;
    spider->free = free_default_loop_header_spider;
    //재료들을 만들다 (Create materials):
    aio_default_loop_header_materials *materials = new_object(sizeof(aio_default_loop_header_materials));
    //Init start state:
    materials->scope_type = AIO_DEFAULT_LOOP_HEADER_DECLARATION_SCOPE;
    materials->declaration_type = AIO_DEFAULT_LOOP_HEADER_VARIABLE_UNDEFINED;
    materials->step_type = AIO_DEFAULT_LOOP_HEADER_STEP_VARIABLE;
    //Init watchers:
    materials->main_watcher = new_point_watcher();
    materials->main_watcher->start = parent_watcher->pointer;
    materials->main_watcher->end = parent_watcher->pointer;
    materials->condition_watcher = new_point_watcher();
    materials->value_watcher = new_point_watcher();
    materials->pointer_data_list = new_str_hook_list();
    //재료들을 놓다 (Set materials):
    spider->materials = materials;
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
#ifdef AIO_DEFAULT_LOOP_HEADER_SPIDER_DEBUG
    log_info(AIO_DEFAULT_LOOP_HEADER_SPIDER_TAG, "Creating is complete!");
#endif
    return spider;
}