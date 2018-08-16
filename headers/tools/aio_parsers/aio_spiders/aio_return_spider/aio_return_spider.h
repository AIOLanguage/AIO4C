#ifndef AIO_RETURN_SPIDER_H
#define AIO_RETURN_SPIDER_H

#include "../aio_spider.h"

typedef enum aio_return_scope_type {
    AIO_RETURN_MODIFIER_SCOPE, AIO_RETURN_VALUE_SCOPE, AIO_RETURN_WEAVING_SCOPE
} aio_return_scope_type;

typedef struct aio_return_materials {
    //State:
    aio_return_scope_type scope_type;
    //Watchers:
    point_watcher *main_watcher;
    point_watcher *value_watcher;
    //Data:
    string_list *value_list;
} aio_return_materials;

struct aio_spider *new_aio_return_spider(point_watcher *ripper_watcher);

const enum aio_spider_message is_found_return_instruction(const_string source_code, point_watcher *ripper_watcher,
                                                          struct aio_spider *spider);

void handle_return_modifier_scope(const_string source_code, struct aio_spider *spider);

void handle_return_value_scope(const_string source_code, struct aio_spider *spider);

void weave_return_instruction_for(aio_instruction_holder *holder, const_string _,
                                  point_watcher *ripper_watcher, struct aio_spider *spider);

#endif //AIO_RETURN_SPIDER_H