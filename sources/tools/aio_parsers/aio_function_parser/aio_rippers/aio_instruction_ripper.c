#include <mem.h>
#include <malloc.h>
#include "../../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../../headers/lang/aio_function/aio_function_definition/aio_instructions/aio_instructions.h"
#include "../../../../../headers/lib/point_watcher/point_watcher.h"
#include "../../../../../headers/lib/utils/char_utils/char_utils.h"
#include "../../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../../headers/lib/utils/string_utils/string_builder.h"
#include "../../../../../headers/tools/aio_parsers/aio_function_parser/aio_rippers/aio_spiders/aio_spider_nest.h"
#include "../../../../../headers/lib/utils/log_utils/log_utils.h"
#include "../../../../../headers/tools/aio_parsers/aio_block_body_explorer/aio_block_body_explorer.h"

#define AIO_INSTRUCTION_RIPPER_DEBUG

#define AIO_INSTRUCTION_RIPPER_TAG "AIO_INSTRUCTION_RIPPER"

aio_instruction_holder *dig_aio_root_instruction_holder(const_string source_code, int *start_code_pointer_ref) {
#ifdef AIO_INSTRUCTION_RIPPER_DEBUG
    log_info(AIO_INSTRUCTION_RIPPER_TAG, "Dig root holder...");
#endif
    //Dig instruction holder:
    aio_instruction_holder *parent_holder = NULL;
    //Pre start with previous start index:
    int start_index = *start_code_pointer_ref;
    int end_index = 0;
    //Init block bounds: start & end indices:
#ifdef AIO_INSTRUCTION_RIPPER_DEBUG
    log_info(AIO_INSTRUCTION_RIPPER_TAG, "Explore function body...");
#endif
    explore_block_body(source_code, &start_index, &end_index);
    *start_code_pointer_ref = end_index;
    aio_instruction_holder *holder = dig_aio_instruction_holder(source_code, parent_holder, start_index, end_index);
    return holder;
}

aio_instruction_holder *dig_aio_instruction_holder(const_string source_code, aio_instruction_holder *parent_holder,
                                                   const int start_index, const int end_index) {
    //Create instruction holder:
    aio_instruction_holder *holder = new_aio_instruction_holder(parent_holder);
    const int body_length = end_index - start_index;
    const_boolean is_not_empty_block = body_length > 2;
    const_boolean starts_with_open_brace = is_open_brace(source_code[start_index]);
    if (is_not_empty_block && starts_with_open_brace) {
        //Create spider swarm for searching instructions:
        aio_spider_nest *spider_nest = breed_aio_function_spider_nest();
        string_builder *str_builder = new_string_builder();
        //Create point ripper_watcher:
        point_watcher *ripper_watcher = new_point_watcher();
        ripper_watcher->pointer = start_index + 1;
        ripper_watcher->start_index = start_index + 1;
        ripper_watcher->end_index = end_index;
        //After weaving instruction need from check function body string rest:
        while (ripper_watcher->pointer < end_index) {
            //Check string content from define:
            //Do spiders need from search instructions or not?
            if (ripper_watcher->mode == POINT_PASSIVE_MODE) {
                if (is_end_of_block_body(source_code, ripper_watcher)) {
                    break;
                }
            }
            //Active mode for spider swarm:
            if (ripper_watcher->mode == POINT_ACTIVE_MODE) {
                //Add symbol in string builder:
                append_char_to(str_builder, source_code[ripper_watcher->pointer]);
                const_string string_web = str_builder->string_value;
                //Give "string web" from spider swarm:
                const aio_spider_swarm_mode swarm_mode = spider_nest->mode;
                if (swarm_mode == AIO_ALL_SPIDERS_WORK) {
                    for (int j = 0; j < spider_nest->number_of_spiders; ++j) {
                        aio_spider *spider = spider_nest->spiders[j];
                        //Spider try from match "string web" with it task:
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
                        //Spider takes current holder and weave for holder instruction:
                        spider->weave_instruction_for(holder, source_code, &ripper_watcher->start_index, spider);
                        //Reset spiders:
                        reset_aio_spiders(spider_nest);
                        //Reset string builder:
                        reset_string_builder(str_builder);
                        //Shift main_watcher:
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