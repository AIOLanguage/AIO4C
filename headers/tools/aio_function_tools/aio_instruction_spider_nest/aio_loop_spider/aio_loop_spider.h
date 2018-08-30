#ifndef AIO_LOOP_SPIDER_H
#define AIO_LOOP_SPIDER_H

/**
 * Default loop header spider.
 */

typedef enum aio_default_loop_header_scope_type {
    AIO_DEFAULT_LOOP_HEADER_DECLARATION_SCOPE,
    AIO_DEFAULT_LOOP_HEADER_EQUAL_SIGN_SCOPE,
    AIO_DEFAULT_LOOP_HEADER_VALUE_SCOPE,
    AIO_DEFAULT_LOOP_HEADER_CONDITION_SCOPE,
    AIO_DEFAULT_LOOP_HEADER_STEP_SCOPE,
    AIO_DEFAULT_LOOP_HEADER_WEAVING_SCOPE
} aio_default_loop_header_scope_type;

typedef enum aio_default_loop_header_pointer_declaration_type {
    AIO_DEFAULT_LOOP_HEADER_VARIABLE_UNDEFINED,
    AIO_DEFAULT_LOOP_HEADER_WAS_MUTABLE_MODIFIER,
    AIO_DEFAULT_LOOP_HEADER_MUTABLE,
    AIO_DEFAULT_LOOP_HEADER_IMMUTABLE,
    AIO_DEFAULT_LOOP_HEADER_REFERENCE,
    AIO_DEFAULT_LOOP_HEADER_ABSENT
} aio_default_loop_header_pointer_declaration_type;

typedef enum aio_default_loop_header_step_type {
    AIO_DEFAULT_LOOP_HEADER_STEP_VARIABLE,
    AIO_DEFAULT_LOOP_HEADER_STEP_EQUAL_SIGN_SCOPE,
    AIO_DEFAULT_LOOP_HEADER_STEP_VALUE_SCOPE
} aio_default_loop_header_step_type;

typedef struct aio_default_loop_header_materials {
    //States:
    enum aio_default_loop_header_scope_type scope_type;
    enum aio_default_loop_header_pointer_declaration_type declaration_type;
    enum aio_default_loop_header_step_type step_type;
    //Watchers:
    struct point_watcher *main_watcher;
    struct point_watcher *value_watcher;
    struct point_watcher *condition_watcher;
    //Data:
    struct str_hook_list *pointer_data_list;
    char *init_value;
    char *loop_condition;
    char *step_value;
} aio_default_loop_header_materials;

struct aio_spider *new_aio_default_loop_header_spider(struct point_watcher *parent_watcher);

const struct str_hook *get_default_loop_pointer_name_by_materials(
        const struct aio_default_loop_header_materials *materials
);

struct aio_variable_definition *create_pointer_variable_definition_by_default_loop_header_spider(
        const enum aio_default_loop_header_pointer_declaration_type declaration_type,
        const struct str_hook **pointer_data
);

/**
 * In loop header spider.
 */

/**
 * Tiny loop header spider.
 */

/**
 * Main loop spider.
 */

typedef enum aio_loop_scope_type {
    AIO_LOOP_MODIFIER_SCOPE, AIO_LOOP_HEADER_SCOPE, AIO_LOOP_BODY_SCOPE, AIO_LOOP_WEAVING_SCOPE
} aio_loop_scope_type;

typedef enum aio_loop_header_material_type {
    AIO_LOOP_MATERIALS_DEFAULT_HEADER,
    AIO_LOOP_MATERIALS_IN_HEADER,
    AIO_LOOP_MATERIALS_TINY_HEADER
} aio_loop_header_material_type;

typedef struct aio_loop_materials {
    //States:
    enum aio_loop_scope_type scope_type;
    //Watchers:
    struct point_watcher *main_watcher;
    struct point_watcher *header_watcher;
    struct point_watcher *body_watcher;
    enum aio_loop_header_material_type applied_header_material_type;
    union {
        struct aio_default_loop_header_materials *default_loop_header;
        struct aio_in_loop_header_materials *in_loop_header;
        struct aio_tiny_loop_header_materials *tiny_loop_header;
    } get;

} aio_loop_materials;

struct aio_spider *new_aio_loop_spider(struct point_watcher *ripper_watcher);

/**
 *  Declare functions.
 */

const enum aio_spider_message is_found_loop_instruction(
        const char *source_code,
        struct point_watcher *ripper_watcher,
        struct aio_spider *spider
);

void handle_loop_modifier_scope(const char *source_code, struct aio_spider *spider);

void handle_loop_header_scope(const char *source_code, struct aio_spider *spider);

struct aio_spider_nest *breed_aio_loop_header_spider_nest(struct point_watcher *header_watcher);

void handle_loop_body_scope(const char *source_code, struct aio_spider *spider);

void dig_header_materials(const char *source_code, struct aio_spider *parent_spider);

void weave_loop_instruction_for(
        void *parent,
        const char *source_code,
        struct point_watcher *ripper_watcher,
        struct aio_spider *spider
);

#endif //AIO_LOOP_SPIDER_H