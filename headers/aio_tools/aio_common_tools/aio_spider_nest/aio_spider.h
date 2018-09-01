#ifndef AIO_SPIDER_H
#define AIO_SPIDER_H

typedef enum aio_spider_message {
    AIO_SPIDER_NOT_FOUND_MATERIALS, AIO_SPIDER_FOUND_MATERIALS, AIO_SPIDER_IS_READY_FOR_WEAVING
} aio_spider_message;

/**
 * Spider.
 */

typedef struct aio_spider {

    enum aio_spider_message message;

    void *materials;

    void (*refresh)(struct aio_spider *current_spider, struct point_watcher *parent_watcher);

    const enum aio_spider_message (*is_found_context)(
            const char *source_code,
            struct point_watcher *parent_watcher,
            struct aio_spider *spider
    );

    void (*weave_context_for)(
            void *holder,
            const char *source_code,
            struct point_watcher *parent_watcher,
            struct aio_spider *current_spider
    );

    void (*free)(struct aio_spider *current_spider);

} aio_spider;

#endif //AIO_SPIDER_H