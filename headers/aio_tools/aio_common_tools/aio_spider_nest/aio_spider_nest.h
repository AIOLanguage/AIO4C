#ifndef AIO_SPIDER_NEST_H
#define AIO_SPIDER_NEST_H

/**
 * Linking.
 */

#include <aio_tools/aio_common_tools/aio_spider_nest/aio_spider_nest.h>
#include <lib/utils/point_watcher/point_watcher.h>

typedef enum aio_spider_nest_mode {
    AIO_ONE_SPIDER_WORKS, AIO_ALL_SPIDERS_WORK
} aio_spider_nest_mode;

typedef struct aio_spider_nest {
    int number_of_spiders;
    struct aio_spider **spiders;
    struct aio_spider *active_spider;
    enum aio_spider_nest_mode mode;
} aio_spider_nest;

void refresh_aio_spider_nest(struct aio_spider_nest *nest, struct str_hook_iterator *parent_iterator);

void free_aio_spider_nest(struct aio_spider_nest *nest);

struct aio_value_list *handle_symbol_for(
        void *instruction_holder,
        struct aio_context *context,
        const char symbol,
        struct aio_bundle *bundle
);

#endif //AIO_SPIDER_NEST_H