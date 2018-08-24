#ifndef AIO_SPIDER_H
#define AIO_SPIDER_H

#include "../../../lib/utils/string_utils/string_utils.h"
#include "../../../lib/utils/point_watcher/point_watcher.h"

typedef enum aio_spider_message {
    AIO_SPIDER_NOT_FOUND_MATERIALS, AIO_SPIDER_FOUND_MATERIALS, AIO_SPIDER_IS_READY_FOR_WEAVING
} aio_spider_message;

/**
 * Spider.
 */

typedef struct aio_spider {

    aio_spider_message message;

    void *materials;

    /**
     * Reset spider's fields.
     */

    void (*refresh)(struct aio_spider *current_spider, point_watcher *parent_watcher);

    /**
     * Find instruction.
     */

    const aio_spider_message (*is_found_context)(const_string source_code, point_watcher *parent_watcher,
                                                     struct aio_spider *spider);

    void (*weave_context_for)(void *holder,
            const_string source_code,
            point_watcher *parent_watcher,
            struct aio_spider *current_spider);

    /**
     * Free spider.
     * @param current_spider - this.
     */

    void (*free)(struct aio_spider *current_spider);

} aio_spider;

#endif //AIO_SPIDER_H