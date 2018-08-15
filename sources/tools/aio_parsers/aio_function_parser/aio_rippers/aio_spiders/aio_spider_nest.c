#include <malloc.h>
#include "../../../../../../headers/tools/aio_parsers/aio_function_parser/aio_rippers/aio_spiders/aio_spider_nest.h"
#include "../../../../../../headers/lib/utils/memory_utils/memory_utils.h"

#define AIO_NUMBER_OF_SPIDERS 2 //7

#define AIO_SPIDER_NEST_DEBUG

#ifdef AIO_SPIDER_NEST_DEBUG

#define AIO_SPIDER_NEST_TAG "AIO_SPIDER_NEST"

#include "../../../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

/**
 * Create spiders
 * @param body_length - specifies end index of function code block.
 * @return array of spiders.
 */

aio_spider_nest *breed_aio_function_spider_nest(point_watcher *ripper_watcher) {
#ifdef AIO_SPIDER_NEST_DEBUG
    log_info_int(AIO_SPIDER_NEST_TAG, "Breed aio function spiders... Number of spiders:", AIO_NUMBER_OF_SPIDERS);
#endif
    //Create spiders:
    aio_spider **spiders = calloc(AIO_NUMBER_OF_SPIDERS, sizeof(aio_spider *));
    spiders[0] = new_aio_assign_spider(ripper_watcher);
    spiders[1] = new_aio_if_spider(ripper_watcher);
//    spiders[2] = new_aio_loop_spider();
//    spiders[2] = new_aio_break_spider();
//    spiders[4] = new_aio_out_spider();
//    spiders[5] = new_aio_procedure_spider();
//    spiders[6] = new_aio_switch_spider();
    //Create
    aio_spider_nest *nest = new_object(sizeof(aio_spider_nest));
    nest->number_of_spiders = AIO_NUMBER_OF_SPIDERS;
    nest->spiders = spiders;
    nest->active_spider = NULL;
    nest->mode = AIO_ALL_SPIDERS_WORK;
#ifdef AIO_SPIDER_NEST_DEBUG
    log_info(AIO_SPIDER_NEST_TAG, "Breeding is complete!");
#endif
    return nest;
}

/**
 * Reset each spider.
 * @param spider nest.
 */

void refresh_aio_spiders(aio_spider_nest *nest, point_watcher *ripper_watcher) {
    for (int i = 0; i < AIO_NUMBER_OF_SPIDERS; ++i) {
        aio_spider *spider = nest->spiders[i];
        //Reset himself:
        spider->refresh(spider, ripper_watcher);
    }
}

/**
 * Destroy nest & free all spiders.
 * @param spider nest.
 */

void free_aio_spider_swarm(aio_spider_nest *nest) {
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