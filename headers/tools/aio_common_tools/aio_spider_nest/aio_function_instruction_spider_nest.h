#ifndef AIO_SPIDER_NEST_H
#define AIO_SPIDER_NEST_H

#include "aio_spider.h"

typedef enum aio_spider_nest_mode {
    AIO_ONE_SPIDER_WORKS, AIO_ALL_SPIDERS_WORK
} aio_spider_nest_mode;

typedef struct aio_spider_nest {
    int number_of_spiders;
    struct aio_spider **spiders;
    struct aio_spider *active_spider;
    aio_spider_nest_mode mode;
} aio_spider_nest;

void refresh_aio_spider_nest(aio_spider_nest *nest, point_watcher *parent_watcher);

void free_aio_spider_nest(aio_spider_nest *nest);

#endif //AIO_SPIDER_NEST_H