#ifndef AIO_PROCEDURE_SPIDER_H
#define AIO_PROCEDURE_SPIDER_H

typedef enum aio_procedure_scope_type {
    AIO_PROCEDURE_NAME_SCOPE, AIO_PROCEDURE_ARG_SCOPE, AIO_PROCEDURE_WEAVING_SCOPE
} aio_procedure_scope_type;

typedef struct aio_procedure_materials {
    enum aio_procedure_scope_type scope_type;
    struct point_watcher *main_watcher;
} aio_procedure_materials;

struct aio_spider *new_aio_procedure_spider(struct point_watcher *ripper_watcher);

const enum aio_spider_message is_found_procedure_instruction(
        const char *source_code,
        struct point_watcher *ripper_watcher,
        struct aio_spider *spider
);

void handle_procedure_name_scope(const char *source_code, struct aio_spider *spider);

void handle_procedure_arg_scope(const char *source_code, struct aio_spider *spider);

void weave_procedure_instruction_for(
        void *parent,
        const char *source_code,
        struct point_watcher *ripper_watcher,
        struct aio_spider *spider
);

#endif //AIO_PROCEDURE_SPIDER_H