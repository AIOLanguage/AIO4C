#ifndef AIO_IF_SPIDER_H
#define AIO_IF_SPIDER_H

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
    enum aio_if_scope_type scope_type;
    enum aio_if_branch_type branch_type;
    //Watchers:
    struct point_watcher *main_watcher;
    struct point_watcher *header_watcher;
    struct point_watcher *true_watcher;
    struct point_watcher *false_watcher;
    //Condition:
    char *condition;
} aio_if_materials;

struct aio_spider *new_aio_if_spider(struct point_watcher *ripper_watcher);

/**
 * Declare functions.
 */

const enum aio_spider_message is_found_if_instruction(
        const char *source_code,
        struct point_watcher *ripper_watcher,
        struct aio_spider *spider
);

void handle_if_modifier_scope(const char *source_code, struct aio_spider *spider);

void handle_condition_scope(const char *source_code, struct aio_spider *spider);

void handle_true_body_scope(const char *source_code, struct aio_spider *spider);

void handle_false_body_scope(const char *source_code, struct aio_spider *spider);

void weave_if_instruction_for(
        void *parent,
        const char *source_code,
        struct point_watcher *ripper_watcher,
        struct aio_spider *spider
);

#endif //AIO_IF_SPIDER_H