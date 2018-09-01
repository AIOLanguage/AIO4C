#ifndef AIO_FUNCTION_DEFINITION_H
#define AIO_FUNCTION_DEFINITION_H

/**
 * Function definition.
 */

typedef struct aio_function_definition {
    struct aio_annotation_list *annotation_list;
    struct str_hook_list *output_type_list;
    struct str_hook *name;
    unsigned int number_of_args;
    struct aio_function_instruction_holder *root_holder;
} aio_function_definition;

struct aio_function_definition *new_aio_function_definition(
        struct aio_annotation_list *annotations,
        struct str_hook_list *output_type_list,
        struct str_hook *name,
        unsigned int number_of_args,
        struct aio_function_instruction_holder *holder
);

void free_aio_function_definition(struct aio_function_definition *function_definition);

/**
 * List.
 */

typedef struct aio_function_definition_list {
    unsigned int capacity;
    unsigned int size;
    struct aio_function_definition **definitions;
} aio_function_definition_list;

struct aio_function_definition_list *new_aio_function_definition_list();

void add_aio_function_definition_in_list(
        struct aio_function_definition_list *list,
        struct aio_function_definition *definition
);

struct aio_function_definition *get_aio_function_definition_in_list_by_name(
        struct aio_function_definition_list *list,
        struct str_hook *name
);

void free_aio_function_definition_list(struct aio_function_definition_list *function_definition_list);

#endif //AIO_FUNCTION_DEFINITION_H