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

//#define AIO_INSTRUCTION_RIPPER_DEBUG

#define AIO_INSTRUCTION_RIPPER_TAG "AIO_INSTRUCTION_RIPPER"

#ifdef AIO_INSTRUCTION_RIPPER_DEBUG

#include "../../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

aio_instruction_holder *dig_aio_root_instruction_holder(const_string source_code, int *start_code_pointer_ref) {
#ifdef AIO_INSTRUCTION_RIPPER_DEBUG
    log_info(AIO_INSTRUCTION_RIPPER_TAG, "Dig root holder...");
#endif
    //보유자를 파다 (Dig a instruction holder):
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
    aio_instruction_holder *holder = dig_aio_instruction_holder(source_code, parent_holder, start_index, end_index);
    return holder;
}

aio_instruction_holder *dig_aio_instruction_holder(const_string source_code, aio_instruction_holder *parent_holder,
                                                   const int start_index, const int end_index) {
    aio_instruction_holder *holder = new_aio_instruction_holder(parent_holder);
    const int body_length = end_index - start_index;
    const_boolean is_not_empty_block = body_length > 2;
    const_boolean starts_with_open_brace = is_open_brace(source_code[start_index]);
    if (is_not_empty_block && starts_with_open_brace) {
        //검색 지침을 위해 거미 무리를 만들다 (Create spider swarm for searching instructions):
        aio_spider_nest *spider_nest = breed_aio_function_spider_nest();
        string_builder *str_builder = new_string_builder();
        //리퍼 당직자 만들다 (Create ripper watcher):
        point_watcher *ripper_watcher = new_point_watcher();
        ripper_watcher->pointer = start_index + 1;
        ripper_watcher->start_index = start_index + 1;
        ripper_watcher->end_index = end_index;
        //지침을 제본후에 함수 블록 나머지 확인하셔야하다 (Need to check function body rest after weaving of instruction):
        while (ripper_watcher->pointer < end_index) {
            //거미가 지침을 검색해야합니까 (Do spiders need to search for instructions)?
            if (ripper_watcher->mode == POINT_PASSIVE_MODE) {
                if (is_end_of_block_body(source_code, ripper_watcher)) {
                    break;
                }
            }
            //거미 무리의 활성 모드: Active mode of spider nest:
            if (ripper_watcher->mode == POINT_ACTIVE_MODE) {
                //줄 빌더에 기호를 추가하다 (Add symbol in string builder):
                append_char_to(str_builder, source_code[ripper_watcher->pointer]);
                const_string string_web = str_builder->string_value;
                const aio_spider_swarm_mode swarm_mode = spider_nest->mode;
                if (swarm_mode == AIO_ALL_SPIDERS_WORK) {
                    for (int j = 0; j < spider_nest->number_of_spiders; ++j) {
                        aio_spider *spider = spider_nest->spiders[j];
                        //거미가 '문자열 웹'에 대한 정규식을 찾으려고합니다
                        //(A spider is trying to find a regex for "string web"):
                        aio_spider_message message = spider->is_found_instruction(string_web, spider);
                        if (message == AIO_SPIDER_FOUND_MATERIALS) {
                            spider_nest->active_spider = spider;
                            spider_nest->mode = AIO_ONE_SPIDER_WORKS;
                            break;
                        }
                    }
                }
                if (swarm_mode == AIO_ONE_SPIDER_WORKS) {
                    aio_spider *spider = spider_nest->active_spider;
                    const aio_spider_message message = spider->is_found_instruction(string_web, spider);
                    if (message == AIO_SPIDER_IS_READY_FOR_WEAVING) {
                        //거미가 현재 보유자를 붙잡고 지침을 길쌈한다:
                        //(A spider takes current holder and weaves instruction):
                        spider->weave_instruction_for(holder, source_code, &ripper_watcher->start_index, spider);
                        //거미들 리셋 (Reset spiders):
                        reset_aio_spiders(spider_nest);
                        //줄 빌더 리셋 (Reset string builder):
                        reset_string_builder(str_builder);
                        //리퍼 당직자를 바꾼다 (Shift ripper watcher):
                        ripper_watcher->pointer = ripper_watcher->start_index;
                        ripper_watcher->mode = POINT_PASSIVE_MODE;
                    }
                }
            }
            ripper_watcher->pointer++;
        }
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free_aio_spider_swarm(spider_nest);
    }
    return holder;
}