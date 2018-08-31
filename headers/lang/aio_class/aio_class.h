#ifndef AIO_CLASS_H
#define AIO_CLASS_H

typedef struct aio_class {
    struct aio_annotation_list *annotation_list;
    struct aio_class_list *interface_list;
    struct aio_field_definition_list *field_definition_list;
    struct aio_function_definition_list *function_definition_list;
} aio_class;

/**
 * List.
 */

typedef struct aio_class_list {
    unsigned capacity;
    unsigned size;
    struct aio_class classes;
} aio_class_list;

struct aio_class_list *new_aio_class_list();

void free_aio_class_list(struct aio_class_list *list);

#endif //AIO_CLASS_H