#include <malloc.h>
#include "../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_spiders/aio_spider.h"
#include "../../../../../../../../headers/lang/aio_function/aio_function_definition/aio_spiders/aio_spider_swarm.h"

#define AIO_NUMBER_OF_SPIDERS 7

/**
 * Reset each spider fields.
 * @param swarm array of spiders.
 */

void reset_aio_spiders(aio_spider_swarm *swarm) {
    for (int i = 0; i < AIO_NUMBER_OF_SPIDERS; ++i) {
        aio_spider *spider = swarm->spiders[i];
        //Reset himself:
        spider->reset(spider);
    }
}

/**
 * Create spiders.
 * @return array of spiders.
 */

aio_spider_swarm *breed_aio_function_spider_swarm() {
    //Create spiders:
    aio_spider **spiders = calloc(AIO_NUMBER_OF_SPIDERS, sizeof(aio_spider *));
    spiders[0] = new_aio_assign_spider();
    spiders[1] = new_aio_break_spider();
    spiders[2] = new_aio_if_spider();
    spiders[3] = new_aio_loop_spider();
    spiders[4] = new_aio_out_spider();
    spiders[5] = new_aio_procedure_spider();
    spiders[6] = new_aio_switch_spider();
    aio_spider_swarm *swarm = calloc(1, sizeof(aio_spider_swarm));
    swarm->number_of_spiders = AIO_NUMBER_OF_SPIDERS;
    swarm->spiders = spiders;
    swarm->active_spider = NULL;
    swarm->mode = AIO_ALL_SPIDERS_WORK;
    return swarm;
}

/**
 * Free all spiders.
 * @param spider_swarm - reference of spider array.
 */

void free_aio_spider_swarm(aio_spider_swarm *spider_swarm) {
    aio_spider **spiders = spider_swarm->spiders;
    for (int i = 0; i < spider_swarm->number_of_spiders; ++i) {
        aio_spider *spider = spiders[i];
        //Spider frees himself:
        spider->free(spider);
    }
    free(spiders);
    free(spider_swarm);
}