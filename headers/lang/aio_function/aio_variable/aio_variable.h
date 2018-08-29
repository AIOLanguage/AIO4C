#ifndef AIO_VARIABLE_H
#define AIO_VARIABLE_H

/**
 * Variable.
 */

typedef enum aio_variable_init_type {
    AIO_VARIABLE_NOT_INITIALIZED, AIO_VARIABLE_INITIALIZED
} aio_variable_init_type;

typedef struct aio_variable {
    struct aio_variable_definition *definition;
    struct aio_value *value;
    enum aio_variable_init_type init_type;
} aio_variable;

struct aio_variable *new_aio_variable_by_definition(
        struct aio_variable_definition *variable_definition,
        struct aio_value *value
);

struct aio_variable *force_get_aio_variable_in_function_control_graph(
        const struct str_hook *variable_name,
        const struct aio_function_control_graph *control_graph
);

struct aio_variable *get_aio_variable_in_function_control_graph(
        const struct str_hook *variable_name,
        const struct aio_function_control_graph *control_graph
);

void free_aio_variable(struct aio_variable *variable);

/**
 * List.
 */

typedef struct aio_variable_list {
    unsigned int capacity;
    unsigned int size;
    struct aio_variable **variables;
} aio_variable_list;

struct aio_variable_list *new_aio_variable_list();

void add_aio_variable_in_list(struct aio_variable_list *list, struct aio_variable *variable);

struct aio_variable *get_aio_variable_in_list_by_name(
        const struct aio_variable_list *list,
        const struct str_hook *name
);

void free_aio_variable_list(const struct aio_variable_list *list);

/**
 * Typedef utils.
 */

typedef const struct aio_variable const_aio_variable;

typedef struct aio_variable **aio_variable_array;

typedef const struct aio_variable **const_aio_variable_array;

typedef const struct aio_variable_list const_aio_variable_list;

#endif //AIO_VARIABLE_H