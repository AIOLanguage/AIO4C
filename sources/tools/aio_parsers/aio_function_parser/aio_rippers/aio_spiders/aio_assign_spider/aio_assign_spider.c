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
 * 함수들을 선언하다 (Declare functions).
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

/**
 * 주 논리 (Business logic).
 */

#define AIO_ASSIGN_SPIDER_DEBUG

#define AIO_ASSIGN_SPIDER_TAG "AIO_ASSIGN_SPIDER"

#ifdef AIO_ASSIGN_SPIDER_DEBUG

#include "../../../../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

/**
 * 리셋 (Reset).
 */

void reset_assign_spider(aio_spider *spider) {
    //거미의 조건 리셋 (Reset spider state):
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    //재료 리셋 (Reset materials):
    aio_assign_materials *materials = spider->get.assign_materials;
    reset_point_watcher(materials->main_watcher);
    reset_point_watcher(materials->value_watcher);
    materials->scope_type = AIO_ASSIGN_DECLARATION_SCOPE;
    materials->declaration_type = AIO_ASSIGN_UNDEFINED_DECLARATION;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    string_list *data_list = materials->variable_data_list;
    free(materials->value);
    free_strings_in_list(data_list);
    free_string_list(data_list);
    //------------------------------------------------------------------------------------------------------------------
    materials->variable_data_list = new_string_list();
}

/**
 * 거미를 비우다 (Free spider).
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
 * 건설자 (Constructor).
 */

struct aio_spider *new_aio_assign_spider() {
    aio_spider *spider = new_object(sizeof(aio_spider));
    //함수들을 놓다 (Put functions):
    spider->reset = reset_assign_spider;
    spider->is_found_instruction = is_found_assign_instruction;
    spider->weave_instruction_for = weave_assign_instruction_for;
    spider->free = free_assign_spider;
    //재료들을 만들다 (Create materials):
    aio_assign_materials *materials = new_object(sizeof(aio_assign_materials));
    materials->scope_type = AIO_ASSIGN_DECLARATION_SCOPE;
    materials->declaration_type = AIO_ASSIGN_UNDEFINED_DECLARATION;
    materials->main_watcher = new_point_watcher();
    materials->value_watcher = new_point_watcher();
    materials->variable_data_list = new_string_list();
    //재료들을 놀다 (Set materials):
    spider->get.assign_materials = materials;
    //시작 메시지 초기화하다 (Init start message):
    spider->message = AIO_SPIDER_NOT_FOUND_MATERIALS;
    return spider;
}

/**
 * 수색 (Searching).
 */

const aio_spider_message is_found_assign_instruction(const_string string_web, aio_spider *spider) {
    //재료들을 추출하다 (Extract materials):
    const aio_assign_materials *materials = spider->get.assign_materials;
    point_watcher *watcher = materials->main_watcher;
    watcher->end_index++;
    //스캐닝 준비 (Prepare for scanning):
    const char last_symbol = string_web[watcher->end_index - 1];
    //간격을 건너 뛰다 (Skip whitespaces):
    //TODO:  코드 복제 (Code duplication)!
    if (watcher->mode == POINT_PASSIVE_MODE) {
        if (is_space_or_line_break(last_symbol)) {
            watcher->start_index++;
        } else {
            watcher->mode = POINT_ACTIVE_MODE;
        }
    }
    //거미 작품 (Spider works):
    if (watcher->mode == POINT_ACTIVE_MODE) {
        if (materials->scope_type == AIO_ASSIGN_DECLARATION_SCOPE) {
            handle_assign_declaration_scope(string_web, spider);
        }
        if (materials->scope_type == AIO_ASSIGN_EQUAL_SIGN_SCOPE) {
            handle_assign_equal_sign_scope(string_web, spider);
            return spider->message;
        }
        if (materials->scope_type == AIO_ASSIGN_VALUE_SCOPE) {
            handle_assign_value_scope(string_web, spider);
        }
    }
    return spider->message;
}

/**
 * 핸들러 (Handlers).
 **/

void handle_assign_declaration_scope(const_string string_web, aio_spider *spider) {
    //재료들을 추출하다 (Extract materials):
    aio_assign_materials *materials = spider->get.assign_materials;
    point_watcher *main_watcher = materials->main_watcher;
    //'문자열 웹'을 확인하다 (Check 'string web'):
    const char current_symbol = string_web[main_watcher->end_index - 1];
    //단어 인 경우 (If was word):
    if (is_space_or_line_break(current_symbol)) {
        string chunk = substring(string_web, main_watcher->start_index, main_watcher->end_index - 1);
        //조건들을 확인하다 (Check conditions):
        const_boolean is_mutable_modifier = is_aio_mutable_modifier(chunk);
        const_boolean is_type = contains_aio_type_in_set(chunk);
        const_boolean is_variable_name = is_word(chunk) && can_use_name(chunk);
        if (materials->declaration_type == AIO_ASSIGN_UNDEFINED_DECLARATION) {
            //어쩌면 문자열이 'mu' 수정 자입니까
            //(Maybe string is the 'mu' modifier)?
            if (is_mutable_modifier) {
                refresh_assign_declaration_scope(spider, chunk, AIO_ASSIGN_WAS_MUTABLE_MODIFIER,
                                                 AIO_SPIDER_FOUND_MATERIALS);
                return;
            }
            //어쩌면 문자열이 유형입니까
            //(Maybe string is a type)?
            if (is_type) {
                refresh_assign_declaration_scope(spider, chunk, AIO_ASSIGN_IMMUTABLE,
                                                 AIO_SPIDER_NOT_FOUND_MATERIALS);
                return;
            }
            //어쩌면 문자열이 변수 이름입니까
            //(Maybe string is a variable name)?
            if (is_variable_name) {
                refresh_assign_declaration_scope(spider, chunk, AIO_ASSIGN_WILL_DEFINED,
                                                 AIO_SPIDER_NOT_FOUND_MATERIALS);
                //범위를 바꾼다 (Change scope):
                materials->scope_type = AIO_ASSIGN_EQUAL_SIGN_SCOPE;
            } else {
                //변수 이름이 아님 (Not a variable name):
                //------------------------------------------------------------------------------------------------------
                //찌꺼기 수집기 (Garbage collector):
                free(chunk);
                return;
            }
        }
        if (materials->declaration_type == AIO_ASSIGN_WAS_MUTABLE_MODIFIER) {
            //어쩌면 문자열이 유형입니까
            //(Maybe string is a type)?
            if (is_type) {
                refresh_assign_declaration_scope(spider, chunk, AIO_ASSIGN_MUTABLE,
                                                 AIO_SPIDER_NOT_FOUND_MATERIALS);
                return;
            }
            //어쩌면 문자열이 변수 이름입니까
            //(Maybe string is a variable name)?
            if (is_variable_name) {
                refresh_assign_declaration_scope(spider, chunk, AIO_ASSIGN_REFERENCE,
                                                 AIO_SPIDER_NOT_FOUND_MATERIALS);
                //범위를 바꾼다 (Change scope):
                materials->scope_type = AIO_ASSIGN_EQUAL_SIGN_SCOPE;
            } else {
                //변수 이름이 아님 (Not a variable name):
                //------------------------------------------------------------------------------------------------------
                //찌꺼기 수집기 (Garbage collector):
                free(chunk);
                return;
            }
        }
        if (materials->declaration_type == AIO_ASSIGN_MUTABLE || materials->declaration_type == AIO_ASSIGN_IMMUTABLE) {
            //변수 이름이어야합니다 (It must be a variable name):
            if (is_variable_name) {
                refresh_assign_declaration_scope(spider, chunk, materials->declaration_type,
                                                 AIO_SPIDER_FOUND_MATERIALS);
                //범위를 바꾼다 (Change scope):
                materials->scope_type = AIO_ASSIGN_EQUAL_SIGN_SCOPE;
            } else {
                throw_error_with_tag(AIO_ASSIGN_SPIDER_TAG, "Invalid variable name!");
            }
        }
    }
}

void refresh_assign_declaration_scope(aio_spider *spider, string chunk, aio_assign_variable_declaration_type type,
                                      aio_spider_message message) {
    //재료들을 추출하다 (Extract materials):
    aio_assign_materials *materials = spider->get.assign_materials;
    string_list *variable_data_list = materials->variable_data_list;
    point_watcher *main_watcher = materials->main_watcher;
    //선언 유형을 바꾼다 (Change declaration type):
    materials->declaration_type = type;
    //명부에게 문자열을 놓다 (Put a string in list):
    add_string_in_list(variable_data_list, chunk);
    //본관 당직자를 바꾼다 (Shift main watcher):
    main_watcher->start_index = main_watcher->end_index;
    main_watcher->mode = POINT_PASSIVE_MODE;
    //메시지를 놓다  (Put a message):
    spider->message = message;
}

void handle_assign_equal_sign_scope(const_string string_web, aio_spider *spider) {
    aio_assign_materials *materials = spider->get.assign_materials;
    point_watcher *main_watcher = materials->main_watcher;
    const int current_position = main_watcher->end_index - 1;
    const char current_symbol = string_web[current_position];
    const_boolean is_equal_sign_symbol = is_equal_sign(current_symbol);
    const_boolean is_whitespace = is_space_or_line_break(current_symbol);
    if (is_whitespace) {
        return;
    }
    if (is_equal_sign_symbol) {
        materials->scope_type = AIO_ASSIGN_VALUE_SCOPE;
        main_watcher->start_index = main_watcher->end_index;
        main_watcher->mode = POINT_PASSIVE_MODE;
        spider->message = AIO_SPIDER_FOUND_MATERIALS;
    } else {
        if (spider->message == AIO_SPIDER_FOUND_MATERIALS) {
            throw_error_with_tag(AIO_ASSIGN_SPIDER_TAG, "Invalid variable definition!");
        }
    }
}

void handle_assign_value_scope(const_string string_web, aio_spider *spider) {
    //재료들을 추출하다 (Extract materials):
    aio_assign_materials *materials = spider->get.assign_materials;
    point_watcher *main_watcher = materials->main_watcher;
    point_watcher *value_watcher = materials->value_watcher;
    const int current_position = main_watcher->end_index - 1;
    const char current_symbol = string_web[current_position];
    const_boolean is_whitespace_cond = is_space_or_line_break(current_symbol);
    const_boolean is_close_parenthesis_cond = is_closing_parenthesis(current_symbol);
    const_boolean is_letter_cond = isalpha(current_symbol);
    const_boolean is_letter_or_number_or_close_parenthesis_cond = isalnum(current_symbol) || is_close_parenthesis_cond;
    const_boolean is_close_brace_cond = is_closing_brace(current_symbol);
    if (is_letter_or_number_or_close_parenthesis_cond && value_watcher->mode == POINT_PASSIVE_MODE) {
        value_watcher->mode = POINT_ACTIVE_MODE;
        return;
    }
    if (is_whitespace_cond && value_watcher->mode == POINT_ACTIVE_MODE) {
        value_watcher->pointer++;
        return;
    }
    if ((is_letter_cond || is_close_brace_cond) && value_watcher->mode == POINT_ACTIVE_MODE) {
        value_watcher->end_index = main_watcher->end_index - value_watcher->pointer - 1;
        //값을 놓다 (Set value):
        string dirty_value = substring(string_web, main_watcher->start_index, value_watcher->end_index);
        string clean_value = squeeze_string(dirty_value);
        materials->value = clean_value;
        //위빙 준비 (Prepare for weaving):
        materials->scope_type = AIO_ASSIGN_WEAVING_SCOPE;
        main_watcher->start_index = main_watcher->end_index;
        spider->message = AIO_SPIDER_IS_READY_FOR_WEAVING;
        //--------------------------------------------------------------------------------------------------------------
        //찌거기 수집기 (Garbage collector):
        free((void *) dirty_value);
    } else {
        value_watcher->mode = POINT_PASSIVE_MODE;
        value_watcher->pointer = 0;
    }
}

/**
 * 위빙이 (Weaving).
 */

void weave_assign_instruction_for(aio_instruction_holder *holder, const_string _,
                                  int *next_ripper_point_reference, aio_spider *spider) {
#ifdef AIO_ASSIGN_SPIDER_DEBUG
    log_info(AIO_ASSIGN_SPIDER_TAG, "Start weaving...");
#endif
    //재료들을 추출하다 (Extract materials):
    const aio_assign_materials *materials = spider->get.assign_materials;
    const_string_array variable_data = materials->variable_data_list->strings;
    const_string value_string = materials->value;
    const point_watcher *watcher = materials->main_watcher;
    const aio_assign_variable_declaration_type declaration_type = materials->declaration_type;
    const_boolean is_ready_for_weaving = materials->scope_type == AIO_ASSIGN_WEAVING_SCOPE;
    if (is_ready_for_weaving) {
        *next_ripper_point_reference += watcher->end_index - 1;
        //변수 정의를 짜다 (Weave variable definition):
        aio_variable_definition *new_definition = create_local_variable_definition(declaration_type, variable_data);
        const_string variable_name = new_definition->name;
        aio_variable_definition *definition = get_local_variable_definition_in_function_tree(variable_name, holder);
        if (definition == NULL) {
            definition = new_definition;
            //지도에게 지역 변수 정의를 놓다 (Put local definition in variable definition map):
            aio_variable_definition_map *map = holder->local_variable_definition_map;
            put_aio_variable_definition_in_map(map, definition);
        } else {
            if (declaration_type != AIO_ASSIGN_WILL_DEFINED) {
                throw_error_with_tag(AIO_ASSIGN_SPIDER_TAG, "Variable already was defined in function tree!");
            }
            if (!definition->is_mutable_by_value) {
                throw_error_with_tag(AIO_ASSIGN_SPIDER_TAG, "Immutable variable can not change value!");
            }
            //----------------------------------------------------------------------------------------------------------
            //찌거기 수집기 (Garbage collector):
            free_aio_variable_definition(new_definition);
        }
        //'Assign' 지침을  짜다 (Weave 'assign' instruction):
        const_string assign_task_source = new_string(value_string);
        const_string assign_task_destination = new_string(variable_name);
        aio_instruction *assign_instruction = new_aio_assign_instruction(holder, assign_task_source,
                                                                         assign_task_destination);
        //명부에게 지침을 추가하다 (Add 'assign' instruction in holder's instructions):
        aio_instruction_list *instruction_list = holder->instruction_list;
        add_aio_instruction_in_list(instruction_list, assign_instruction);
        //위빙이 완료되었습니다 (Weaving complete)!
#ifdef AIO_ASSIGN_SPIDER_DEBUG
        log_info(AIO_ASSIGN_SPIDER_TAG, "WEAVED INSTRUCTION:");
        log_info_string(AIO_ASSIGN_SPIDER_TAG, "VARIABLE:", assign_instruction->get.assign_task->destination);
        log_info_string(AIO_ASSIGN_SPIDER_TAG, "VALUE:", assign_instruction->get.assign_task->source);
#endif
    } else {
        throw_error_with_tag(AIO_ASSIGN_SPIDER_TAG, "Not ready for weaving!");
    }
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
        case AIO_ASSIGN_IMMUTABLE:
            variable_name = new_string(variable_materials[1]);
            variable_type = new_string(variable_materials[0]);
            is_mutable = FALSE;
            break;
        case AIO_ASSIGN_MUTABLE:
            variable_name = new_string(variable_materials[2]);
            variable_type = new_string(variable_materials[0]);
            is_mutable = TRUE;
            break;
        default:
            throw_error_with_tag(AIO_ASSIGN_SPIDER_TAG, "Undefined variable declaration mode for weaving!");
    }
    return new_aio_variable_definition(variable_name, variable_type, is_mutable);
}