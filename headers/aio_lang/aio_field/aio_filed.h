#ifndef AIO_FIELD_H
#define AIO_FIELD_H

/**
 * Field.
 */

typedef enum aio_field_init_type {
    AIO_FIELD_NOT_INITIALIZED, AIO_FIELD_INITIALIZED
} aio_field_init_type;

typedef struct aio_filed {
    struct aio_field_definition *definition;
    struct aio_value *value;
    enum aio_field_init_type init_type;
} aio_field;

struct aio_field *new_aio_field_by_definition(
        struct aio_field_definition *field_definition,
        struct aio_value *value
);

void free_aio_field(struct aio_field *filed);

/**
 * List.
 */

typedef struct aio_field_list {
    unsigned int capacity;
    unsigned int size;
    struct aio_field **fields;
} aio_field_list;

struct aio_field_list *new_aio_field_list();

void add_aio_field_in_list(struct aio_field_list *list, struct aio_field *field);

struct aio_field *get_aio_field_in_list_by_name(
        struct aio_field_list *list,
        struct str_hook *name
);

void free_aio_field_list(struct aio_field_list *list);

#endif //AIO_FIELD_H