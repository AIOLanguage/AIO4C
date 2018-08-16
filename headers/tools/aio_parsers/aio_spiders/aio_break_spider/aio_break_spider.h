#ifndef AIO_BREAK_SPIDER_H
#define AIO_BREAK_SPIDER_H

#include "../../../../lib/point_watcher/point_watcher.h"
#include "../aio_spider.h"

/**
 * Break spider materials.
 */

typedef struct aio_break_materials {
    point_watcher *watcher;
} aio_break_materials;

struct aio_spider *new_aio_break_spider(point_watcher *ripper_watcher);

const enum aio_spider_message is_found_break_instruction(const_string source_code, point_watcher *ripper_watcher,
                                                         struct aio_spider *spider);

void handle_break_scope(const_string source_code, struct aio_spider *spider);

void weave_break_instruction_for(aio_instruction_holder *instruction_holder, const_string _,
                                 point_watcher *ripper_watcher, struct aio_spider *spider);

#endif //AIO_BREAK_SPIDER_H