#ifndef AIO_FIELD_DEFINITION_H
#define AIO_FIELD_DEFINITION_H

/**
 * Variable definition.
 */

typedef struct aio_filed_definition {
    const struct str_hook *name;
    struct str_hook *type;
    _Bool is_mutable;
    enum aio_visibility_type visibility_type;
} aio_field_definition;

struct aio_filed_definition *new_aio_field_definition(
        const struct str_hook *name,
        struct str_hook *type,
        const _Bool is_mutable_by_value,
        const enum aio_visibility_type visibility_type
);

const struct aio_filed_definition *request_aio_field_definition(
        const struct str_hook *variable_name,
        const struct aio_function_instruction_holder *holder
);

void free_aio_field_definition(struct aio_filed_definition *definition);

/**
 * List.
 */

typedef struct aio_field_definition_list {
    unsigned int capacity;
    unsigned int size;
    struct aio_filed_definition **definitions;
} aio_field_definition_list;

struct aio_field_definition_list *new_aio_field_definition_list();

void add_aio_field_definition_in_list(
        struct aio_field_definition_list *list,
        struct aio_filed_definition *definition
);

const struct aio_filed_definition *get_aio_field_definition_in_list_by_name(
        const struct aio_field_definition_list *list,
        const struct str_hook *name
);

void free_aio_field_definition_list(aio_field_definition_list *list);

/**
 * Log utils.
 */

void log_info_aio_field_definition(const char *tag, const struct aio_filed_definition *definition);

#endif //AIO_FIELD_DEFINITION_H