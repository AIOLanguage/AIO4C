#include <mem.h>
#include <malloc.h>
#include "../../../../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../../../headers/lib/point_watcher/point_watcher.h"
#include "../../../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../../../headers/lib/utils/string_utils/string_builder.h"
#include "../../../../../../../headers/lang/aio_function/aio_function_definition/aio_spider/aio_spiders.h"

const_string dig_function_body(const_string source_code, int *pointer_reference);


const_boolean has_function_content_rest(const_string function_body_string, const int position, const size_t length);

aio_instruction_holder *dig_instruction_holder(const_string source_code, int *pointer_reference,
                                               aio_instruction_holder *parent_holder) {
    //Create instruction holder:
    aio_instruction_holder *current_holder = new_aio_instruction_holder(parent_holder);
    //Dig function body:
    const_string function_body = dig_function_body(source_code, pointer_reference);
    const size_t function_body_length = strlen(function_body);
    if (function_body_length >= 0) {
        //Create spider swarm for searching instructions:
        aio_spider_swarm *spider_swarm = breed_aio_spider_swarm();
        string_builder *str_builder = new_string_builder();
        //Start to find instruction:
        point_watcher *watcher = new_point_watcher();
        //After weaving instruction need to check function body string rest:
        boolean is_needed_check_body = TRUE;
        for (watcher->pointer; watcher->pointer < function_body_length; ++watcher->pointer) {
            const char symbol = function_body[watcher->pointer];
            //Check string content to define:
            //Do spiders need to search instructions or not?
            if (is_needed_check_body) {
                is_needed_check_body = FALSE;
                if (!has_function_content_rest(function_body, watcher->pointer, function_body_length)) {
                    break;
                } else {
                    watcher->mode = POINT_PASSIVE_MODE;
                }
            }
            //Skip whitespaces and line breaks:
            if (watcher->mode == POINT_PASSIVE_MODE) {
                if (is_space_or_line_break(symbol)) {
                    watcher->pointer++;
                } else {
                    watcher->mode = POINT_ACTIVE_MODE;
                }
            }
            //Active mode for spider swarm:
            if (watcher->mode == POINT_ACTIVE_MODE) {
                //Add symbol in string builder:
                append_char_to(str_builder, symbol);
                const_string string_web = str_builder->string_value;
                //Give "string web" to spider swarm:
                const enum aio_spider_swarm_mode swarm_mode = spider_swarm->mode;
                if (swarm_mode == AIO_ONE_SPIDER_WORKS) {
                    aio_spider *spider = spider_swarm->active_spider;
                    const enum aio_spider_message message = spider->is_found_instruction(string_web, spider);
                    if (message == AIO_SPIDER_WAS_CRUSH) {
                        throw_error("INSTRUCTION RIPPER: invalid context!");
                    }
                    if (message == AIO_SPIDER_IS_READY_FOR_WEAVING) {
                        //Spider takes current holder and weave for holder instruction:
                        spider->weave_instruction_for(current_holder, &watcher->start_index, spider);
                        reset_aio_spiders(spider_swarm);
                        reset_string_builder(str_builder);
                        watcher->pointer = watcher->start_index;
                        is_needed_check_body = TRUE;
                    }
                }
                if (swarm_mode == AIO_ALL_SPIDERS_WORK) {
                    for (int j = 0; j < AIO_NUMBER_OF_SPIDERS; ++j) {
                        aio_spider *spider = spider_swarm->spiders[j];
                        //Spider try to match "string web" with it task:
                        enum aio_spider_message message = spider->is_found_instruction(string_web, spider);
                        if (message == AIO_SPIDER_FOUND_MATERIALS) {
                            spider_swarm->active_spider = spider;
                            spider_swarm->mode = AIO_ONE_SPIDER_WORKS;
                        }
                        if (message == AIO_SPIDER_WAS_CRUSH) {
                            throw_error("INSTRUCTION RIPPER: invalid context!");
                        }
                    }
                }
            }
        }
        free_aio_spider_swarm(spider_swarm);
    }
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free((void *) function_body);
    return current_holder;
}

const_string dig_function_body(const_string source_code, int *pointer_reference) {
    const size_t source_code_length = strlen(source_code);
    point_watcher *watcher = new_point_watcher();
    //함수 바지 멜빵 찾다 (Find function braces):
    for (int i = *pointer_reference; i < source_code_length; ++i) {
        const char symbol = source_code[i];
        const_boolean is_open_brace_condition = is_open_brace(symbol);
        //독서를 시작하다 (Begin reading):
        if (is_open_brace_condition && watcher->mode == POINT_PASSIVE_MODE) {
            watcher->start_index = i + 1;
            watcher->mode = POINT_ACTIVE_MODE;
            watcher->pointer++;
        }
        if (is_open_brace_condition && watcher->mode == POINT_ACTIVE_MODE) {
            watcher->pointer++;
        }
        //독서 중지 (Stop reading):
        if (is_close_brace(symbol) && watcher->mode == POINT_ACTIVE_MODE) {
            watcher->pointer--;
            if (watcher->pointer == 0) {
                watcher->end_index = i;
                *pointer_reference = i + 1;
                break;
            }
        }
        //지켜보기 잔에 공백과 줄 바꿈 건너 뙤기 (Skip whitespace and line breaks before watching):
        if (watcher->mode == POINT_PASSIVE_MODE) {
            if (!is_space_or_line_break(symbol)) {
                throw_error("INSTRUCTION RIPPER: 잘못된 함수 함유량 (Invalid function content)!");
            }
        }
    }
    //Dig function body:
    const_string dirty_function_body = substring(source_code, watcher->start_index, watcher->end_index);
    const_string clean_function_body = trim_with_line_break(dirty_function_body);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    free_point_watcher(watcher);
    free((void *) dirty_function_body);
    return clean_function_body;
}

const_boolean has_function_content_rest(const_string function_body_string, const int position, const size_t length) {
    for (int i = position; i < length; ++i) {
        const char symbol = function_body_string[i];
        if (!is_space_or_line_break(symbol)) {
            return TRUE;
        }
    }
    return FALSE;
}