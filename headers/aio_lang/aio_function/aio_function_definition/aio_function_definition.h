#ifndef AIO_FUNCTION_DEFINITION_H
#define AIO_FUNCTION_DEFINITION_H

/**
 * Function definition.
 */

typedef struct aio_function_definition {
    const struct aio_annotation_list *annotation_list;
    const struct str_hook_list *output_type_list;
    const struct str_hook *name;
    unsigned int number_of_args;
    const struct aio_function_instruction_holder *root_holder;
} aio_function_definition;

const struct aio_function_definition *new_aio_function_definition(
        const struct aio_annotation_list *annotations,
        const struct str_hook_list *output_type_list,
        const struct str_hook *name,
        const unsigned int number_of_args,
        const struct aio_function_instruction_holder *holder
);

void free_aio_function_definition(const struct aio_function_definition *function_definition);

/**
 * List.
 */

typedef struct aio_function_definition_list {
    unsigned int capacity;
    unsigned int size;
    const struct aio_function_definition **definitions;
} aio_function_definition_list;

struct aio_function_definition_list *new_aio_function_definition_list();

void add_aio_function_definition_in_list(
        struct aio_function_definition_list *list,
        const struct aio_function_definition *definition
);

const struct aio_function_definition *get_aio_function_definition_in_list_by_name(
        const struct aio_function_definition_list *list,
        const struct str_hook *name
);

void free_aio_function_definition_list(struct aio_function_definition_list *function_definition_list);

/**
 * Typedef utils.
 */

typedef const aio_function_definition const_aio_function_definition;

typedef const aio_function_definition_list const_aio_function_definition_list;

#endif //AIO_FUNCTION_DEFINITION_H