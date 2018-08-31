#ifndef AIO_VARIABLE_H
#define AIO_VARIABLE_H

#include <lang/aio_variable/aio_variable.h>
#include <lib/utils/str_hook/str_hook.h>

/**
 * Variable.
 */

typedef enum aio_variable_init_type {
    AIO_VARIABLE_NOT_INITIALIZED, AIO_VARIABLE_INITIALIZED
} aio_variable_init_type;

typedef struct aio_filed {
    struct aio_variable_definition *definition;
    struct aio_value *value;
    enum aio_variable_init_type init_type;
} aio_variable;

struct aio_filed *new_aio_variable_by_definition(
        struct aio_variable_definition *variable_definition,
        struct aio_value *value
);

void free_aio_variable(struct aio_filed *variable);

/**
 * List.
 */

typedef struct aio_variable_list {
    unsigned int capacity;
    unsigned int size;
    struct aio_filed **variables;
} aio_variable_list;

struct aio_variable_list *new_aio_variable_list();

void add_aio_variable_in_list(struct aio_variable_list *list, struct aio_filed *variable);

struct aio_filed *get_aio_variable_in_list_by_name(
        const struct aio_variable_list *list,
        const struct str_hook *name
);

void free_aio_variable_list(const struct aio_variable_list *list);

/**
 * Typedef utils.
 */

typedef const struct aio_filed const_aio_variable;

typedef struct aio_filed **aio_variable_array;

typedef const struct aio_filed **const_aio_variable_array;

typedef const struct aio_variable_list const_aio_variable_list;

#endif //AIO_VARIABLE_H