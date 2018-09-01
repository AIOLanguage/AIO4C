#ifndef AIO_RETURN_SPIDER_H
#define AIO_RETURN_SPIDER_H

typedef enum aio_return_scope_type {
    AIO_RETURN_MODIFIER_SCOPE, AIO_RETURN_VALUE_SCOPE, AIO_RETURN_WEAVING_SCOPE
} aio_return_scope_type;

typedef struct aio_return_materials {
    //State:
    enum aio_return_scope_type scope_type;
    //Watchers:
    struct point_watcher *main_watcher;
    struct point_watcher *value_watcher;
    //Data:
    struct string_list *value_list;
} aio_return_materials;

struct aio_spider *new_aio_return_spider(struct point_watcher *ripper_watcher);

const enum aio_spider_message is_found_return_instruction(
        const char *source_code,
        struct point_watcher *ripper_watcher,
        struct aio_spider *spider
);

void handle_return_modifier_scope(const char *source_code, struct aio_spider *spider);

void handle_return_value_scope(const char *source_code, struct aio_spider *spider);

void weave_return_instruction_for(
        void *parent,
        const char *_,
        struct point_watcher *ripper_watcher,
        struct aio_spider *spider
);

#endif //AIO_RETURN_SPIDER_H