#ifndef AIO_SWITCH_SPIDER_H
#define AIO_SWITCH_SPIDER_H

#include "../aio_spider.h"

typedef enum aio_switch_scope_type {
    AIO_SWITCH_MODIFIER_SCOPE, AIO_HEADER_SCOPE, AIO_BODY_SCOPE, AIO_SWITCH_WEAVING_SCOPE
} aio_switch_scope_type;

typedef enum aio_switch_case_scope_type {
    AIO_SWITCH_CASE_VALUE_SCOPE, AIO_SWITCH_CASE_POINTER_SCOPE, AIO_SWITCH_CASE_BODY_SCOPE
} aio_switch_case_scope_type;

typedef struct aio_switch_materials {
    aio_switch_scope_type scope_type;
    aio_switch_case_scope_type case_scope_type;
    point_watcher *main_watcher;
    point_watcher *case_watcher;

} aio_switch_materials;

struct aio_spider *new_aio_switch_spider(point_watcher *ripper_watcher);

#endif //AIO_SWITCH_SPIDER_H