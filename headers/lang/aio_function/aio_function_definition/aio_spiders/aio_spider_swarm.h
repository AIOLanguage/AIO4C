#ifndef AIO_SPIDER_SWARM_H
#define AIO_SPIDER_SWARM_H

#include "aio_spider.h"

/**
 * Swarm.
 */

typedef enum aio_spider_swarm_mode {
    AIO_ONE_SPIDER_WORKS, AIO_ALL_SPIDERS_WORK
} aio_spider_swarm_mode;

typedef struct aio_spider_swarm {
    int number_of_spiders;
    aio_spider **spiders;
    aio_spider *active_spider;
    aio_spider_swarm_mode mode;
} aio_spider_swarm;

void reset_aio_spiders(aio_spider_swarm *swarm);

aio_spider_swarm *breed_aio_function_spider_swarm();

void free_aio_spider_swarm(aio_spider_swarm *spider_swarm);

#endif //AIO_SPIDER_SWARM_H