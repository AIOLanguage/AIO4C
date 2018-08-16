#ifndef AIO_PROCEDURE_SPIDER_H
#define AIO_PROCEDURE_SPIDER_H

#include "../aio_spider.h"

typedef struct aio_procedure_materials {
    point_watcher *watcher;
} aio_procedure_materials;


struct aio_spider *new_aio_procedure_spider(point_watcher *ripper_watcher);

const enum aio_spider_message is_found_procedure_instruction(const_string source_code, point_watcher *ripper_watcher,
                                                             struct aio_spider *spider);

void handle_procedure_scope(const_string source_code, struct aio_spider *spider);

void weave_procedure_instruction_for(aio_instruction_holder *holder, const_string source_code,
                                     point_watcher *ripper_watcher, struct aio_spider *spider);

#endif //AIO_PROCEDURE_SPIDER_H