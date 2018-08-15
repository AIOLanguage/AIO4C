#include <mem.h>
#include <malloc.h>
#include "../../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../headers/lib/point_watcher/point_watcher.h"
#include "../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../headers/lib/utils/string_utils/string_builder.h"
#include "../../../../../headers/tools/aio_parsers/aio_function_parser/aio_rippers/aio_spiders/aio_spider_nest.h"
#include "../../../../../headers/tools/aio_parsers/aio_block_body_explorer/aio_block_body_explorer.h"
#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"

#define AIO_INSTRUCTION_RIPPER_DEBUG

#define AIO_INSTRUCTION_RIPPER_TAG "AIO_INSTRUCTION_RIPPER"

#ifdef AIO_INSTRUCTION_RIPPER_DEBUG

#include "../../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

aio_instruction_holder *dig_aio_root_instruction_holder(const_string source_code, int *start_code_pointer_ref,
                                                        aio_variable_definition_map *arg_definition_map) {
#ifdef AIO_INSTRUCTION_RIPPER_DEBUG
    log_info(AIO_INSTRUCTION_RIPPER_TAG, "Dig root root_holder...");
#endif
    //보유자를 파다 (Dig a instruction root_holder):
    aio_instruction_holder *parent_holder = NULL;
    //시작 및 종료 인덱스 초기화 (Init start & end indexes):
    int start_index = *start_code_pointer_ref;
    int end_index = 0;
#ifdef AIO_INSTRUCTION_RIPPER_DEBUG
    log_info(AIO_INSTRUCTION_RIPPER_TAG, "Explore function body...");
#endif
    //시작 및 종료 인덱스 찾다 (Search start & end indexes):
    explore_block_body(source_code, &start_index, &end_index);
    *start_code_pointer_ref = end_index;
    aio_instruction_holder *root_holder = new_object(sizeof(struct aio_instruction_holder));
    root_holder->parent = parent_holder;
    root_holder->variable_definition_map = arg_definition_map;
    root_holder->instruction_list = new_aio_instruction_list();
    dig_aio_instructions_for(root_holder, source_code, start_index, end_index);
    return root_holder;
}

aio_instruction_holder *dig_new_aio_instruction_holder(const_string source_code, aio_instruction_holder *parent_holder,
                                                       const int start_index, const int end_index) {
    aio_instruction_holder *holder = new_aio_local_instruction_holder(parent_holder);
    dig_aio_instructions_for(holder, source_code, start_index, end_index);
    return holder;
}

void dig_aio_instructions_for(aio_instruction_holder *current_holder, const_string source_code,
                              const int start_index, const int end_index) {
    const int body_length = end_index - start_index;
    const_boolean is_not_empty_block = body_length > 2;
    const_boolean starts_with_open_brace = is_opening_brace(source_code[start_index]);
#ifdef AIO_INSTRUCTION_RIPPER_DEBUG
    log_info_boolean(AIO_INSTRUCTION_RIPPER_TAG, "Is not empty block:", is_not_empty_block);
    log_info_boolean(AIO_INSTRUCTION_RIPPER_TAG, "Starts with open brace:", starts_with_open_brace);
#endif
    if (is_not_empty_block && starts_with_open_brace) {
        //리퍼 당직자 만들다 (Create ripper watcher):
        point_watcher *ripper_watcher = new_point_watcher();
        ripper_watcher->pointer = start_index + 1;
        ripper_watcher->start_index = start_index + 1;
        ripper_watcher->end_index = end_index;
        //검색 지침을 위해 거미 무리를 만들다 (Create spider swarm for searching instructions):
        aio_spider_nest *spider_nest = breed_aio_function_spider_nest(ripper_watcher);
        //지침을 제본후에 함수 블록 나머지 확인하셔야하다 (Need to check function body rest after weaving of instruction):
        while (ripper_watcher->pointer < end_index) {
            //거미가 지침을 검색해야합니까 (Do spiders need to search for instructions)?
            if (ripper_watcher->mode == POINT_PASSIVE_MODE) {
                if (is_end_of_block_body(source_code, ripper_watcher)) {
                    break;
                } else {
                    refresh_aio_spiders(spider_nest, ripper_watcher);
                }
            }
            //거미 무리의 활성 모드: Active mode of spider nest:
            if (ripper_watcher->mode == POINT_ACTIVE_MODE) {
                //줄 빌더에 기호를 추가하다 (Add symbol in string builder):
                const aio_spider_nest_mode nest_mode = spider_nest->mode;
                if (nest_mode == AIO_ALL_SPIDERS_WORK) {
                    for (int j = 0; j < spider_nest->number_of_spiders; ++j) {
                        aio_spider *spider = spider_nest->spiders[j];
                        //거미가 '문자열 웹'에 대한 정규식을 찾으려고합니다
                        //(A spider is trying to find a regex for "string web"):
                        aio_spider_message message = spider->is_found_instruction(source_code, ripper_watcher, spider);
                        if (message == AIO_SPIDER_FOUND_MATERIALS) {
#ifdef AIO_INSTRUCTION_RIPPER_DEBUG
                            log_info(AIO_INSTRUCTION_RIPPER_TAG, "One spider works:");
#endif
                            spider_nest->active_spider = spider;
                            spider_nest->mode = AIO_ONE_SPIDER_WORKS;
                            break;
                        }
                    }
                }
                if (nest_mode == AIO_ONE_SPIDER_WORKS) {
                    aio_spider *spider = spider_nest->active_spider;
                    const aio_spider_message message = spider->is_found_instruction(source_code,
                                                                                    ripper_watcher, spider);
                    if (message == AIO_SPIDER_IS_READY_FOR_WEAVING) {
                        //거미가 현재 보유자를 붙잡고 지침을 길쌈한다:
                        //(A spider takes current holder and weaves instruction):
                        spider->weave_instruction_for(current_holder, source_code, ripper_watcher, spider);
                        //Refresh spiders:
                        refresh_aio_spiders(spider_nest, ripper_watcher);
                        //리퍼 당직자를 바꾼다 (Shift ripper watcher):
#ifdef AIO_INSTRUCTION_RIPPER_DEBUG
                        log_info_char(AIO_INSTRUCTION_RIPPER_TAG, "mCharacter:",
                                      source_code[ripper_watcher->pointer - 4]);
                        log_info_char(AIO_INSTRUCTION_RIPPER_TAG, "mCharacter:",
                                      source_code[ripper_watcher->pointer - 3]);
                        log_info_char(AIO_INSTRUCTION_RIPPER_TAG, "mCharacter:",
                                      source_code[ripper_watcher->pointer - 2]);
                        log_info_char(AIO_INSTRUCTION_RIPPER_TAG, "<>:",
                                      source_code[ripper_watcher->pointer - 1]);
                        log_info_char(AIO_INSTRUCTION_RIPPER_TAG, "mCharacter:",
                                      source_code[ripper_watcher->pointer]);
#endif
                        ripper_watcher->mode = POINT_PASSIVE_MODE;
                        //거미 무리 리셋 (Spider nest refresh):
                        spider_nest->mode = AIO_ALL_SPIDERS_WORK;
                        spider_nest->active_spider = NULL;
#ifdef AIO_INSTRUCTION_RIPPER_DEBUG
                        log_info(AIO_INSTRUCTION_RIPPER_TAG, "All spiders work:");
#endif
                    }
                }
            }
            ripper_watcher->pointer++;
        }
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free_aio_spider_swarm(spider_nest);
    }
}