#ifndef AIO_ASSIGN_SPIDER_H
#define AIO_ASSIGN_SPIDER_H

/**
 * Linking.
 */

#include <tools/aio_common_tools/aio_spider_nest/aio_spider.h>
#include <lib/utils/str_hook/str_hook.h>

/**
 * Assign spider materials.
 */

typedef enum aio_assign_scope_type {
    AIO_ASSIGN_DECLARATION_SCOPE, AIO_ASSIGN_EQUAL_SIGN_SCOPE, AIO_ASSIGN_VALUE_SCOPE, AIO_ASSIGN_WEAVING_SCOPE
} aio_assign_scope_type;

typedef enum aio_assign_variable_declaration_type {
    AIO_ASSIGN_UNDEFINED_DECLARATION, AIO_ASSIGN_WAS_MUTABLE_MODIFIER, AIO_ASSIGN_WILL_DEFINED, AIO_ASSIGN_REFERENCE,
    AIO_ASSIGN_IMMUTABLE, AIO_ASSIGN_MUTABLE
} aio_assign_variable_declaration_type;

typedef struct aio_assign_materials {
    //States:
    enum aio_assign_scope_type scope_type;
    enum aio_assign_variable_declaration_type declaration_type;
    //Watchers:
    struct point_watcher *main_watcher;
    struct point_watcher *value_watcher;
    //Variable:
    struct str_hook_list *variable_data_list;
    //Value:
    char *value;
} aio_assign_materials;

struct aio_spider *new_aio_assign_spider(struct point_watcher *ripper_watcher);

const enum aio_spider_message is_found_assign_instruction(
        const char *source_code,
        struct point_watcher *ripper_watcher,
        struct aio_spider *spider
);

void handle_assign_declaration_scope(const char *source_code, struct aio_spider *spider);

void refresh_assign_declaration_scope(
        struct aio_spider *spider,
        const struct str_hook *hook,
        enum aio_assign_variable_declaration_type type,
        enum aio_spider_message message
);

void handle_assign_equal_sign_scope(const char *source_code, struct aio_spider *spider);

void handle_assign_value_scope(const char *source_code, struct aio_spider *spider);

void weave_assign_instruction_for(
        void *holder,
        const char *_,
        struct point_watcher *ripper_watcher,
        struct aio_spider *spider
);

#endif //AIO_ASSIGN_SPIDER_H