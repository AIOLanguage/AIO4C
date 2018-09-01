#ifndef AIO_BREAK_SPIDER_H
#define AIO_BREAK_SPIDER_H

/**
 * Break spider materials.
 */

typedef struct aio_break_materials {
    struct point_watcher *watcher;
} aio_break_materials;

struct aio_spider *new_aio_break_spider(struct point_watcher *ripper_watcher);

const enum aio_spider_message is_found_break_instruction(
        const char *source_code,
        struct point_watcher *ripper_watcher,
        struct aio_spider *spider
);

void handle_break_scope(const char *source_code, struct aio_spider *spider);

void weave_break_instruction_for(
        void *parent,
        const char *_,
        struct point_watcher *ripper_watcher,
        struct aio_spider *spider
);

#endif //AIO_BREAK_SPIDER_H