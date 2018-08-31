#ifndef AIO_VARIABLE_DEFINITION_H
#define AIO_VARIABLE_DEFINITION_H

/**
 * Variable definition.
 */

typedef struct aio_filed_definition {
    enum aio_visibility_type visibility_type;
    const struct str_hook *name;
    struct str_hook *type;
    _Bool is_mutable;
} aio_variable_definition;

struct aio_filed_definition *new_aio_variable_definition(
        const struct str_hook *name,
        struct str_hook *type,
        const _Bool is_mutable_by_value
);

const struct aio_filed_definition *get_aio_variable_definition_in_function_tree(
        const struct str_hook *variable_name,
        const struct aio_function_instruction_holder *holder
);

void free_aio_variable_definition(struct aio_filed_definition *definition);

/**
 * List.
 */

typedef struct aio_variable_definition_list {
    unsigned int capacity;
    unsigned int size;
    struct aio_filed_definition **definitions;
} aio_variable_definition_list;

struct aio_variable_definition_list *new_aio_variable_definition_list();

void add_aio_variable_definition_in_list(
        struct aio_variable_definition_list *list,
        struct aio_filed_definition *definition
);

const struct aio_filed_definition *get_aio_variable_definition_in_map_by_name(
        const struct aio_variable_definition_list *list,
        const struct str_hook *name
);

void free_aio_variable_definition_list(struct aio_variable_definition_list *list);

/**
 * Log utils.
 */

void log_info_aio_variable_definition(const char *tag, const struct aio_filed_definition *definition);

/**
 * Typedef utils.
 */

typedef const struct aio_filed_definition const_aio_variable_definition;

typedef const struct aio_variable_definition_list const_aio_variable_definition_list;

#endif //AIO_VARIABLE_DEFINITION_H