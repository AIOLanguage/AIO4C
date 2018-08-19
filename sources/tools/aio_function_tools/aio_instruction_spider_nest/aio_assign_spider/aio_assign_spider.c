#include <mem.h>
#include <ctype.h>
#include "../../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../headers/lang/aio_reserved_names/aio_reserved_names_container.h"
#include "../../../../../headers/lang/aio_core/aio_core.h"
#include "../../../../../headers/lib/utils/string_utils/string_builder.h"
#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/tools/aio_common_tools/aio_spider_nest/aio_spider.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instruction_spider_nest/aio_assign_spider/aio_assign_spider.h"
#include "../../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"
#include "../../../../../headers/lang/aio_function/aio_variable/aio_definition/aio_variable_definition.h"
#include "../../../../../headers/tools/aio_function_tools/aio_instructions/aio_tasks/aio_assign_task.h"
#include "../../../../../headers/lang/aio_type/aio_type.h"

/**
 * 주 논리 (Business logic).
 */

#define AIO_ASSIGN_SPIDER_DEBUG

#define AIO_ASSIGN_SPIDER_TAG "AIO_ASSIGN_SPIDER"

#ifdef AIO_ASSIGN_SPIDER_DEBUG

#include "../../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

void refresh_assign_spider(aio_spider *spider, point_watcher *ripper_watcher) {
    //거미의 조건 리셋 (Reset spider state):
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    //재료 리셋 (Reset materials):
    aio_assign_materials *materials = spider->materials;
    point_watcher *main_watcher = materials->main_watcher;
    main_watcher->start = ripper_watcher->pointer;
    main_watcher->end = ripper_watcher->pointer;
    main_watcher->mode = POINT_PASSIVE_MODE;
    reset_point_watcher(materials->value_watcher);
    materials->scope_type = AIO_ASSIGN_DECLARATION_SCOPE;
    materials->declaration_type = AIO_ASSIGN_UNDEFINED_DECLARATION;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    str_hook_list *data_list = materials->variable_data_list;
    free(materials->value);
    free_str_hooks_in_list(data_list);
    free_str_hook_list(data_list);
    //------------------------------------------------------------------------------------------------------------------
    materials->variable_data_list = new_str_hook_list();
}

/**
 * 거미를 비우다 (Free spider).
 */

void free_assign_spider(aio_spider *spider) {
    aio_assign_materials *materials = spider->materials;
    free_point_watcher(materials->main_watcher);
    free_point_watcher(materials->value_watcher);
    free_str_hooks_in_list(materials->variable_data_list);
    free_str_hook_list(materials->variable_data_list);
    free(materials->value);
    free(materials);
    free(spider);
}

/**
 * 건설자 (Constructor).
 */

struct aio_spider *new_aio_assign_spider(point_watcher *ripper_watcher) {
    aio_spider *spider = new_object(sizeof(aio_spider));
    //함수들을 놓다 (Put functions):
    spider->refresh = refresh_assign_spider;
    spider->is_found_context = is_found_assign_instruction;
    spider->weave_context_for = weave_assign_instruction_for;
    spider->free = free_assign_spider;
    //재료들을 만들다 (Create materials):
    aio_assign_materials *materials = new_object(sizeof(aio_assign_materials));
    materials->scope_type = AIO_ASSIGN_DECLARATION_SCOPE;
    materials->declaration_type = AIO_ASSIGN_UNDEFINED_DECLARATION;
    materials->main_watcher = new_point_watcher();
    materials->main_watcher->start = ripper_watcher->start;
    materials->main_watcher->end = ripper_watcher->pointer;
    materials->value_watcher = new_point_watcher();
    materials->variable_data_list = new_str_hook_list();
    //재료들을 놀다 (Set materials):
    spider->materials = materials;
    //시작 메시지 초기화하다 (Init start message):
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    return spider;
}

/**
 * 수색 (Searching).
 */

const aio_spider_message is_found_assign_instruction(const_string source_code, point_watcher *ripper_watcher,
                                                     aio_spider *spider) {
    //재료들을 추출하다 (Extract materials):
    const aio_assign_materials *materials = spider->materials;
    point_watcher *main_watcher = materials->main_watcher;
    main_watcher->end = ripper_watcher->pointer;
    //스캐닝 준비 (Prepare for scanning):
    const char current_symbol = source_code[main_watcher->end];
    //간격을 건너 뛰다 (Skip whitespaces):
    //TODO:  코드 복제 (Code duplication)!
    if (main_watcher->mode == POINT_PASSIVE_MODE) {
        if (is_space_or_line_break(current_symbol)) {
            main_watcher->start++;
        } else {
            main_watcher->mode = POINT_ACTIVE_MODE;
        }
    }
    //거미 작품 (Spider works):
    if (main_watcher->mode == POINT_ACTIVE_MODE) {
        if (materials->scope_type == AIO_ASSIGN_DECLARATION_SCOPE) {
            handle_assign_declaration_scope(source_code, spider);
        }
        if (materials->scope_type == AIO_ASSIGN_EQUAL_SIGN_SCOPE) {
            handle_assign_equal_sign_scope(source_code, spider);
            return spider->message;
        }
        if (materials->scope_type == AIO_ASSIGN_VALUE_SCOPE) {
            handle_assign_value_scope(source_code, spider);
        }
    }
    return spider->message;
}

/**
 * 핸들러 (Handlers).
 **/

void handle_assign_declaration_scope(const_string source_code, aio_spider *spider) {
    //재료들을 추출하다 (Extract materials):
    aio_assign_materials *materials = spider->materials;
    point_watcher *main_watcher = materials->main_watcher;
    //'문자열 웹'을 확인하다 (Check 'string web'):
    const char current_symbol = source_code[main_watcher->end];
#ifdef AIO_ASSIGN_SPIDER_DEBUG
    //log_info_char(AIO_ASSIGN_SPIDER_TAG, "Current symbol:", current_symbol);
#endif
    //단어 인 경우 (If was word):
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    const_boolean is_equal_sign_cond = is_equal_sign(current_symbol);
    if (is_whitespace_cond || is_equal_sign_cond) {
        const_str_hook *hook = new_str_hook_by_point_watcher(source_code, main_watcher);
#ifdef AIO_ASSIGN_SPIDER_DEBUG
        log_info_string_hook(AIO_ASSIGN_SPIDER_TAG, "CAPTURE CHUNK:", hook);
#endif
        //조건들을 확인하다 (Check conditions):
        const_boolean is_mutable_modifier = is_aio_mutable_modifier_hooked(hook);
        const_boolean is_type = is_aio_type_hooked(hook);
        const_boolean is_variable_name = is_word_hooked(hook) && can_use_name(hook);
        if (materials->declaration_type == AIO_ASSIGN_UNDEFINED_DECLARATION) {
            //어쩌면 문자열이 'mu' 수정 자입니까
            //(Maybe string is the 'mu' modifier)?
            if (is_mutable_modifier) {
                refresh_assign_declaration_scope(spider, hook, AIO_ASSIGN_WAS_MUTABLE_MODIFIER,
                                                 AIO_SPIDER_FOUND_MATERIALS);
                return;
            }
            //어쩌면 문자열이 유형입니까
            //(Maybe string is a type)?
            if (is_type) {
                refresh_assign_declaration_scope(spider, hook, AIO_ASSIGN_IMMUTABLE,
                                                 AIO_SPIDER_NOT_FOUND_MATERIALS);
                return;
            }
            //어쩌면 문자열이 변수 이름입니까
            //(Maybe string is a variable name)?
            if (is_variable_name) {
                refresh_assign_declaration_scope(spider, hook, AIO_ASSIGN_WILL_DEFINED,
                                                 AIO_SPIDER_NOT_FOUND_MATERIALS);
                //범위를 바꾼다 (Change scope):
                materials->scope_type = AIO_ASSIGN_EQUAL_SIGN_SCOPE;
            } else {
                //변수 이름이 아님 (Not a variable name):
                //------------------------------------------------------------------------------------------------------
                //찌꺼기 수집기 (Garbage collector):
                free_const_str_hook(hook);
                return;
            }
        }
        if (materials->declaration_type == AIO_ASSIGN_WAS_MUTABLE_MODIFIER) {
            //어쩌면 문자열이 유형입니까
            //(Maybe string is a type)?
            if (is_type) {
                refresh_assign_declaration_scope(spider, hook, AIO_ASSIGN_MUTABLE,
                                                 AIO_SPIDER_FOUND_MATERIALS);
                return;
            }
            //어쩌면 문자열이 변수 이름입니까
            //(Maybe string is a variable name)?
            if (is_variable_name) {
                refresh_assign_declaration_scope(spider, hook, AIO_ASSIGN_REFERENCE,
                                                 AIO_SPIDER_FOUND_MATERIALS);
                //범위를 바꾼다 (Change scope):
                materials->scope_type = AIO_ASSIGN_EQUAL_SIGN_SCOPE;
            } else {
                //변수 이름이 아님 (Not a variable name):
                //------------------------------------------------------------------------------------------------------
                //찌꺼기 수집기 (Garbage collector):
                free_const_str_hook(hook);
                return;
            }
        }
        if (materials->declaration_type == AIO_ASSIGN_MUTABLE || materials->declaration_type == AIO_ASSIGN_IMMUTABLE) {
            //변수 이름이어야합니다 (It must be a variable name):
            if (is_variable_name) {
                refresh_assign_declaration_scope(spider, hook, materials->declaration_type,
                                                 AIO_SPIDER_FOUND_MATERIALS);
                //범위를 바꾼다 (Change scope):
                materials->scope_type = AIO_ASSIGN_EQUAL_SIGN_SCOPE;
            } else {
                throw_error_with_tag(AIO_ASSIGN_SPIDER_TAG, "Invalid variable name!");
            }
        }
    }
}

void refresh_assign_declaration_scope(aio_spider *spider, const_str_hook *hook,
                                      aio_assign_variable_declaration_type type,
                                      aio_spider_message message) {
    //재료들을 추출하다 (Extract materials):
    aio_assign_materials *materials = spider->materials;
    str_hook_list *variable_data_list = materials->variable_data_list;
    point_watcher *main_watcher = materials->main_watcher;
    //선언 유형을 바꾼다 (Change declaration type):
    materials->declaration_type = type;
    //명부에게 문자열을 놓다 (Put a string in list):
    add_str_hook_in_list(variable_data_list, hook);
#ifdef AIO_ASSIGN_SPIDER_DEBUG
    log_info_string_hook(AIO_ASSIGN_SPIDER_TAG, "ADD>>>:", hook);
#endif
    //본관 당직자를 바꾼다 (Shift main watcher):
    main_watcher->start = main_watcher->end + 1;
    main_watcher->mode = POINT_PASSIVE_MODE;
    //메시지를 놓다  (Put a message):
    spider->message = message;
}

void handle_assign_equal_sign_scope(const_string source_code, aio_spider *spider) {
    aio_assign_materials *materials = spider->materials;
    point_watcher *main_watcher = materials->main_watcher;
    const int current_position = main_watcher->end;
    const char current_symbol = source_code[current_position];
    const_boolean is_equal_sign_cond = is_equal_sign(current_symbol);
    const_boolean is_whitespace = is_space_or_line_break(current_symbol);
    if (is_whitespace) {
        return;
    }
    if (is_equal_sign_cond) {
        materials->scope_type = AIO_ASSIGN_VALUE_SCOPE;
        main_watcher->start = main_watcher->end + 1;
        main_watcher->mode = POINT_PASSIVE_MODE;
        spider->message = AIO_SPIDER_FOUND_MATERIALS;
#ifdef AIO_ASSIGN_SPIDER_DEBUG
        log_info(AIO_ASSIGN_SPIDER_TAG, "Found equal sign!");
#endif
    } else {
        if (spider->message == AIO_SPIDER_FOUND_MATERIALS) {
            throw_error_with_tag(AIO_ASSIGN_SPIDER_TAG, "Invalid variable definition!");
        }
    }
}

void handle_assign_value_scope(const_string source_code, aio_spider *spider) {
    //재료들을 추출하다 (Extract materials):
    aio_assign_materials *materials = spider->materials;
    point_watcher *main_watcher = materials->main_watcher;
    point_watcher *value_watcher = materials->value_watcher;
    const int current_position = main_watcher->end;
    const char current_symbol = source_code[current_position];
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    const_boolean is_letter_cond = isalpha(current_symbol);
    const_boolean is_valid_bound = isalnum(current_symbol)
                                   || is_closing_parenthesis(current_symbol)
                                   || is_single_quote(current_symbol);
    const_boolean is_close_brace_cond = is_closing_brace(current_symbol);
    if (is_whitespace_cond && value_watcher->mode == POINT_ACTIVE_MODE) {
        value_watcher->pointer++;
        return;
    }
    if (((is_letter_cond && value_watcher->pointer > 0) || is_close_brace_cond)
        && value_watcher->mode == POINT_ACTIVE_MODE) {
        value_watcher->start = main_watcher->start;
        value_watcher->end = main_watcher->end - value_watcher->pointer;
        //값을 놓다 (Set value):
        string dirty_value = substring_by_point_watcher(source_code, value_watcher);
        string clean_value = squeeze_string(dirty_value);
        materials->value = clean_value;
#ifdef AIO_ASSIGN_SPIDER_DEBUG
        log_info_string(AIO_ASSIGN_SPIDER_TAG, "CAPTURED VALUE:", clean_value);
#endif
        //위빙 준비 (Prepare for weaving):
        materials->scope_type = AIO_ASSIGN_WEAVING_SCOPE;
        main_watcher->start = main_watcher->end;
        spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
        //--------------------------------------------------------------------------------------------------------------
        //찌거기 수집기 (Garbage collector):
        free((void *) dirty_value);
    } else {
        value_watcher->mode = POINT_PASSIVE_MODE;
        value_watcher->pointer = 0;
        if (is_valid_bound) {
            value_watcher->mode = POINT_ACTIVE_MODE;
            return;
        }
    }
}

/**
 * 위빙이 (Weaving).
 */

static const_str_hook * get_definition_name_by_materials(const aio_assign_materials *materials) {
    const_str_hook_array variable_data = materials->variable_data_list->hooks;
    const aio_assign_variable_declaration_type declaration_type = materials->declaration_type;
    const_str_hook *variable_name = NULL;
    switch (declaration_type) {
        case AIO_ASSIGN_WILL_DEFINED:
            variable_name = variable_data[0];
            break;
        case AIO_ASSIGN_REFERENCE:
        case AIO_ASSIGN_IMMUTABLE:
            variable_name = variable_data[1];
            break;
        case AIO_ASSIGN_MUTABLE:
            variable_name = variable_data[2];
            break;
        default:
            throw_error_with_tag(AIO_ASSIGN_SPIDER_TAG, "Undefined variable declaration mode for weaving!");
    }
    return variable_name;
}


static aio_variable_definition *create_local_variable_definition(
        const aio_assign_variable_declaration_type declaration_type,
        const_str_hook_array variable_materials) {
    const_str_hook *variable_name = NULL;
    str_hook *variable_type = NULL;
    boolean is_mutable = FALSE;
    switch (declaration_type) {
        case AIO_ASSIGN_WILL_DEFINED:
            variable_name = new_str_hook_by_other(variable_materials[0]);
            variable_type = new_str_hook_by_string(AIO_WILL_DEFINED);
            break;
        case AIO_ASSIGN_REFERENCE:
            variable_name = new_str_hook_by_other(variable_materials[1]);
            variable_type = new_str_hook_by_string(VOID);
            is_mutable = TRUE;
            break;
        case AIO_ASSIGN_IMMUTABLE:
            variable_name = new_str_hook_by_other(variable_materials[1]);
            variable_type = new_str_hook_by_other(variable_materials[0]);
            break;
        case AIO_ASSIGN_MUTABLE:
            variable_name = new_str_hook_by_other(variable_materials[2]);
            variable_type = new_str_hook_by_other(variable_materials[0]);
            is_mutable = TRUE;
            break;
        default:
            throw_error_with_tag(AIO_ASSIGN_SPIDER_TAG, "Undefined variable declaration mode for weaving!");
    }
    return new_aio_variable_definition(variable_name, variable_type, is_mutable);
}

void weave_assign_instruction_for(void *holder, const_string _,
                                  point_watcher *ripper_watcher, aio_spider *spider) {
#ifdef AIO_ASSIGN_SPIDER_DEBUG
    log_info(AIO_ASSIGN_SPIDER_TAG, "Start weaving...");
#endif
    aio_function_instruction_holder *instruction_holder = holder;
    //재료들을 추출하다 (Extract materials):
    const aio_assign_materials *materials = spider->materials;
    const_str_hook_array variable_data = materials->variable_data_list->hooks;
    const_string value_string = materials->value;
    const aio_assign_variable_declaration_type declaration_type = materials->declaration_type;
    const_boolean is_ready_for_weaving = materials->scope_type == AIO_ASSIGN_WEAVING_SCOPE;
    if (is_ready_for_weaving) {
        ripper_watcher->pointer = materials->value_watcher->end;
        ripper_watcher->start = materials->value_watcher->end;
        //변수 정의를 짜다 (Weave variable definition):
        const_str_hook *definition_name = get_definition_name_by_materials(materials);
        const_aio_variable_definition *definition = get_variable_definition_in_function_tree(definition_name, holder);
        if (definition == NULL) {
            definition = create_local_variable_definition(declaration_type, variable_data);;
            //지도에게 지역 변수 정의를 놓다 (Put local definition in variable definition list):
            aio_variable_definition_list *list = instruction_holder->variable_definition_list;
            add_aio_variable_definition_in_list(list, definition);
        } else {
#ifdef AIO_ASSIGN_SPIDER_DEBUG
            log_info_string_hook(AIO_ASSIGN_SPIDER_TAG, "<FOUND DEFINITION>:", definition->name);
            log_info_string_hook(AIO_ASSIGN_SPIDER_TAG, "<TYPE>:", definition->type);
            log_info_boolean(AIO_ASSIGN_SPIDER_TAG, "<IS MUTABLE>:", definition->is_mutable_by_value);
#endif
            if (declaration_type != AIO_ASSIGN_WILL_DEFINED) {
                throw_error_with_tag(AIO_ASSIGN_SPIDER_TAG, "Variable already was defined in function tree!");
            }
            if (!definition->is_mutable_by_value) {
                throw_error_with_details(AIO_ASSIGN_SPIDER_TAG, "Immutable variable can not change value!",
                                         substring_by_str_hook(definition->name));
            }
        }
        //'Assign' 지침을  짜다 (Weave 'Assign' instruction):
        const_string task_value = new_string(value_string);
        const_str_hook *task_variable_name = new_str_hook_by_other(definition->name);
        aio_function_instruction *instruction = new_aio_assign_instruction(holder, task_value, task_variable_name);
        //명부에게 지침을 추가하다 (Add 'assign' instruction in holder's instructions):
        aio_function_instruction_list *instruction_list = instruction_holder->instruction_list;
        add_aio_instruction_in_list(instruction_list, instruction);
        //위빙이 완료되었습니다 (Weaving complete)!
#ifdef AIO_ASSIGN_SPIDER_DEBUG
        log_info(AIO_ASSIGN_SPIDER_TAG, "WEAVED INSTRUCTION:");
        log_info_string_hook(AIO_ASSIGN_SPIDER_TAG, "VARIABLE:", instruction->get.assign_task->variable_name);
        log_info_string(AIO_ASSIGN_SPIDER_TAG, "VALUE:", instruction->get.assign_task->value);
#endif
    } else {
        throw_error_with_tag(AIO_ASSIGN_SPIDER_TAG, "Not ready for weaving!");
    }
}