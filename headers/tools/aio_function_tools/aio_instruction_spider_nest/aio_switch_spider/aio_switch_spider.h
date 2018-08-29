#ifndef AIO_SWITCH_SPIDER_H
#define AIO_SWITCH_SPIDER_H

typedef enum aio_switch_scope_type {
    AIO_SWITCH_MODIFIER_SCOPE, AIO_SWITCH_HEADER_SCOPE, AIO_SWITCH_BODY_SCOPE, AIO_SWITCH_WEAVING_SCOPE
} aio_switch_scope_type;

typedef struct aio_switch_materials {
    //States:
    enum aio_switch_scope_type scope_type;
    _Bool has_else_branch;
    //Watchers:
    struct point_watcher *main_watcher;
    struct point_watcher *header_watcher;
    struct point_watcher *switch_body_watcher;
    struct point_watcher *else_watcher;
    //String hooks:
    struct str_hook_list *case_key_list;
    struct str_hook_list *case_body_list;
} aio_switch_materials;

struct aio_spider *new_aio_switch_spider(struct point_watcher *ripper_watcher);

const enum aio_spider_message is_found_switch_instruction(
        const char *source_code,
        struct point_watcher *ripper_watcher,
        struct aio_spider *spider
);

void handle_switch_modifier_scope(const char *source_code, struct aio_spider *spider);

void handle_switch_header_scope(const char *source_code, struct aio_spider *spider);

void handle_switch_body_scope(const char *source_code, struct aio_spider *spider);

void build_switch_cases(const char *source_code, struct aio_spider *spider);

void handle_switch_case_value_scope(const char *source_code, struct aio_spider *spider);

void handle_switch_case_body_scope(const char *source_code, struct aio_spider *spider);

void weave_switch_instruction_for(
        void *parent,
        const char *source_code,
        struct point_watcher *ripper_watcher,
        struct aio_spider *spider
);

struct string_list *extract_case_keys_from_hook(const struct str_hook *case_keys_hook);

#endif //AIO_SWITCH_SPIDER_H