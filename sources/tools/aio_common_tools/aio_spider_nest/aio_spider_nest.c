#include <mem.h>
#include <malloc.h>
#include <tools/aio_common_tools/aio_spider_nest/aio_function_instruction_spider_nest.h>
#include <tools/aio_common_tools/aio_spider_nest/aio_spider.h>
#include <lib/utils/string_utils/string_utils.h>
#include <lib/utils/str_hook/str_hook.h>
#include <lib/utils/str_hook/str_hook_utils/str_hook_utils.h>

#define AIO_SPIDER_NEST_DEBUG

#define AIO_SPIDER_NEST_TAG "AIO_SPIDER_NEST"

#ifdef AIO_SPIDER_NEST_DEBUG

#endif

/**
 * Refresh each spider.
 * @param spider nest.
 */

void refresh_aio_spider_nest(aio_spider_nest *nest, point_watcher *parent_watcher)
{
    for (int i = 0; i < nest->number_of_spiders; ++i) {
        aio_spider *spider = nest->spiders[i];
        spider->refresh(spider, parent_watcher);
    }
}

/**
 * Destroy nest & free all spiders.
 * @param spider nest.
 */

void free_aio_spider_nest(aio_spider_nest *nest)
{
    aio_spider **spiders = nest->spiders;
    for (int i = 0; i < nest->number_of_spiders; ++i) {
        aio_spider *spider = spiders[i];
        //Spider frees himself:
        spider->free(spider);
    }
    free(spiders);
    free(nest);
}

static void make_instruction_weaving(
        const_string source_code,
        point_watcher *nest_watcher,
        aio_spider *spider,
        aio_spider_nest *spider_nest,
        void *holder
)
{
    //거미가 현재 보유자를 붙잡고 지침을 길쌈한다:
    //(A spider takes current holder and weaves instruction):
    spider->weave_context_for(holder, source_code, nest_watcher, spider);
    //Refresh spiders:
    refresh_aio_spider_nest(spider_nest, nest_watcher);
    //리퍼 당직자를 바꾼다 (Shift ripper watcher):
    nest_watcher->mode = POINT_WATCHER_PASSIVE_MODE;
    //거미 무리 리셋 (Spider nest refresh):
    spider_nest->mode = AIO_ALL_SPIDERS_WORK;
    spider_nest->active_spider = NULL;
}

void search_context_for(
        void *holder,
        const_str_hook *source_code_hook,
        aio_spider_nest *(*breed_spider_nest)(const_str_hook *)
)
{
    const_boolean is_not_empty_block = get_str_hook_size(source_code_hook) > 2;
    if (is_not_empty_block) {
        //검색 지침을 위해 거미 무리를 만들다 (Create spider nest for searching instructions):
        aio_spider_nest *spider_nest = breed_spider_nest(source_code_hook);
        //지침을 제본후에 함수 블록 나머지 확인하셔야하다 (Need to check function body rest after weaving of instruction):
        while (ripper_watcher->pointer < end_index) {
            //거미가 지침을 검색해야합니까 (Do spiders need to search for instructions)?
            if (ripper_watcher->mode == POINT_WATCHER_PASSIVE_MODE) {
                if (has_context_rest(source_code_hook, ripper_watcher)) {
                    break;
                } else {
                    refresh_aio_spider_nest(spider_nest, ripper_watcher);
                }
            }
            //거미 무리의 활성 모드: Active mode of spider nest:
            if (ripper_watcher->mode == POINT_WATCHER_ACTIVE_MODE) {
                //줄 빌더에 기호를 추가하다 (Add symbol in string builder):
                const aio_spider_nest_mode nest_mode = spider_nest->mode;
                if (nest_mode == AIO_ALL_SPIDERS_WORK) {
                    for (int j = 0; j < spider_nest->number_of_spiders; ++j) {
                        aio_spider *spider = spider_nest->spiders[j];
                        //거미가 '문자열 웹'에 대한 정규식을 찾으려고합니다
                        //(A spider is trying to find a regex for "string web"):
                        aio_spider_message message = spider->is_found_context(source_code_hook, ripper_watcher, spider);
                        if (message == AIO_SPIDER_FOUND_MATERIALS) {
#ifdef AIO_INSTRUCTION_RIPPER_DEBUG
                            log_info(AIO_INSTRUCTION_RIPPER_TAG, "One spider works:");
#endif
                            spider_nest->active_spider = spider;
                            spider_nest->mode = AIO_ONE_SPIDER_WORKS;
                            break;
                        }
                        if (message == AIO_SPIDER_IS_READY_FOR_WEAVING) {
                            make_instruction_weaving(source_code_hook, ripper_watcher, spider, spider_nest, holder);
                        }
                    }
                }
                if (nest_mode == AIO_ONE_SPIDER_WORKS) {
                    aio_spider *spider = spider_nest->active_spider;
                    const aio_spider_message message = spider->is_found_context(source_code_hook, ripper_watcher,
                                                                                spider);
                    if (message == AIO_SPIDER_IS_READY_FOR_WEAVING) {
                        make_instruction_weaving(source_code_hook, ripper_watcher, spider, spider_nest, holder);
                    }
                }
            }
            ripper_watcher->pointer++;
        }
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기 (Garbage collector):
        free_aio_spider_nest(spider_nest);
    }
}