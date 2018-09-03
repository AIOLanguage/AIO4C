#include <mem.h>
#include <malloc.h>
#include <lib/utils/string_utils/string_utils.h>
#include <lib/utils/str_hook/str_hook.h>
#include <lib/utils/str_hook/str_hook_utils/str_hook_utils.h>
#include <aio_tools/aio_common_tools/aio_spider_nest/aio_spider_nest.h>
#include <lib/utils/type_utils/type.utils.h>
#include <aio_tools/aio_common_tools/aio_spider_nest/aio_abstract_spider/aio_spider.h>
#include <aio_core/aio_context/aio_context.h>
#include <aio_tools/aio_common_tools/aio_utils/aio_bundle/aio_bundle.h>
#include <aio_tools/aio_common_tools/aio_utils/aio_value/aio_value.h>

#define AIO_SPIDER_NEST_DEBUG

#define AIO_SPIDER_NEST_TAG "AIO_SPIDER_NEST"

#ifdef AIO_SPIDER_NEST_DEBUG

#endif

void reset_aio_spider_nest(aio_spider_nest *nest)
{
    for (int i = 0; i < nest->number_of_spiders; ++i) {
        aio_spider *spider = nest->spiders[i];
        spider->reset(spider);
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

static aio_value_list *handle_weaving(
        void *instruction_holder,
        aio_spider *spider,
        aio_context *context,
        aio_bundle *bundle
)
{
    var result = NULL;
    val spider_nest = context->spider_nest;
    result = spider->weave_context_for(instruction_holder, spider, context,  bundle);
    reset_aio_spider_nest(spider_nest);
    spider_nest->mode = AIO_ALL_SPIDERS_WORK;
    spider_nest->active_spider = NULL;
    return result;
}

aio_value_list *handle_symbol_for(
        void *instruction_holder,
        aio_context *context,
        const char symbol,
        aio_bundle *bundle
)
{
    var result = NULL;
    val spider_nest = context->spider_nest;
    val nest_mode = spider_nest->mode;
    if (nest_mode == AIO_ALL_SPIDERS_WORK) {
        for (int j = 0; j < spider_nest->number_of_spiders; ++j) {
            val spider = spider_nest->spiders[j];
            val message = spider->is_found_context(symbol, spider);
            if (message == AIO_SPIDER_FOUND_MATERIALS) {
                spider_nest->active_spider = spider;
                spider_nest->mode = AIO_ONE_SPIDER_WORKS;
                break;
            }
            if (message == AIO_SPIDER_IS_READY_FOR_WEAVING) {
                result = handle_weaving(instruction_holder, spider, context, bundle);
                break;
            }
        }
    }
    if (nest_mode == AIO_ONE_SPIDER_WORKS) {
        val spider = spider_nest->active_spider;
        val message = spider->is_found_context(symbol, spider);
        if (message == AIO_SPIDER_IS_READY_FOR_WEAVING) {
            result = handle_weaving(instruction_holder, spider, context, bundle);
        }
    }
    return result;
}