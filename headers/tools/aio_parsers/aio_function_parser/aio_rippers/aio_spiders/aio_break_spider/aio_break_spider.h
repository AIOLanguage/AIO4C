#ifndef AIO_BREAK_SPIDER_H
#define AIO_BREAK_SPIDER_H

#include "../../../../../../lib/point_watcher/point_watcher.h"
#include "../aio_spider.h"

/**
 * Break spider materials.
 */

typedef struct aio_break_materials {
    point_watcher *watcher;
} aio_break_materials;

struct aio_spider *new_aio_break_spider();

#endif //AIO_BREAK_SPIDER_H