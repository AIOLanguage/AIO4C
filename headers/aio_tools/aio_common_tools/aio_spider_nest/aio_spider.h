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

    void (*refresh)(
            struct str_hook_iterator *parent_iterator,
            struct aio_spider *spider
    );

    enum aio_spider_message (*is_found_context)(
            const char current_symbol,
            struct aio_spider *spider
    );

    void (*weave_context_for)(
            void *parent,
            struct str_hook_iterator *parent_iterator,
            struct aio_spider *spider
    );

    void (*free)(struct aio_spider *spider);

} aio_spider;

#endif //AIO_SPIDER_H