#ifndef AIO_IF_SPIDER_H
#define AIO_IF_SPIDER_H

#include "../../../../lib/point_watcher/point_watcher.h"
#include "../aio_spider.h"

/**
 * If spider materials:
 */

typedef enum aio_if_scope_type {
    AIO_IF_MODIFIER_SCOPE, AIO_IF_CONDITION_SCOPE, AIO_IF_TRUE_BODY_SCOPE, AIO_IF_FALSE_BODY_SCOPE, AIO_IF_WEAVING_SCOPE
} aio_if_scope_type;

typedef enum aio_if_branch_type {
    AIO_UNDEFINED_BRANCHES, AIO_HAS_TRUE_BRANCH, AIO_HAS_TRUE_AND_FALSE_BRANCHES
} aio_if_branch_type;

typedef struct aio_if_materials {
    //States:
    aio_if_scope_type scope_type;
    aio_if_branch_type branch_type;
    //Watchers:
    point_watcher *main_watcher;
    point_watcher *header_watcher;
    point_watcher *true_watcher;
    point_watcher *false_watcher;
    //Condition:
    string condition;
} aio_if_materials;

struct aio_spider *new_aio_if_spider(point_watcher *ripper_watcher);

/**
 * Declare functions.
 */

const enum aio_spider_message is_found_if_instruction(const_string source_code, point_watcher *ripper_watcher,
                                                      struct aio_spider *spider);

void handle_if_modifier_scope(const_string source_code, struct aio_spider *spider);

void handle_condition_scope(const_string string_web, struct aio_spider *spider);

void handle_true_body_scope(const_string source_code, struct aio_spider *spider);

void handle_false_body_scope(const_string source_code, struct aio_spider *spider);

void weave_if_instruction_for(aio_instruction_holder *holder, const_string source_code, point_watcher *ripper_watcher,
                              struct aio_spider *spider);

#endif //AIO_IF_SPIDER_H