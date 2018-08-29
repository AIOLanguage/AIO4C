#include <malloc.h>
#include "../../../../headers/tools/aio_common_tools/aio_spider_nest/aio_function_instruction_spider_nest.h"
#include "../../../../headers/lib/utils/point_watcher/point_watcher.h"
#include "../../../../headers/tools/aio_common_tools/aio_spider_nest/aio_spider.h"

//#define AIO_SPIDER_NEST_DEBUG

#define AIO_SPIDER_NEST_TAG "AIO_SPIDER_NEST"

#ifdef AIO_SPIDER_NEST_DEBUG

#include "../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

/**
 * Refresh each spider.
 * @param spider nest.
 */

void refresh_aio_spider_nest(aio_spider_nest *nest, point_watcher *parent_watcher)
{
#ifdef AIO_SPIDER_NEST_DEBUG
    log_info_int(AIO_SPIDER_NEST_TAG, "Number of spiders:", nest->number_of_spiders);
#endif
    for (int i = 0; i < nest->number_of_spiders; ++i) {
#ifdef AIO_SPIDER_NEST_DEBUG
        log_info(AIO_SPIDER_NEST_TAG, "Get spider:");
#endif
        aio_spider *spider = nest->spiders[i];
#ifdef AIO_SPIDER_NEST_DEBUG
        log_info_int(AIO_SPIDER_NEST_TAG, "START TO REFRESH", i);
#endif
        spider->refresh(spider, parent_watcher);
#ifdef AIO_SPIDER_NEST_DEBUG
        log_info_int(AIO_SPIDER_NEST_TAG, "END TO REFRESH", i);
#endif
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
#ifdef AIO_SPIDER_NEST_DEBUG
    log_info(AIO_SPIDER_NEST_TAG, "Spider nest is destroyed!");
#endif
}