#ifndef AIO_CORE_H
#define AIO_CORE_H

#define NUMBER_OF_CORE_TYPES 5

typedef struct aio_core {
    //Main:
    struct str_hook_list *aio_type_set;
    struct aio_context_list *context_list;
    //Data:
    struct aio_function_definition_list *global_function_definition_list;
    struct aio_field_definition_list *global_field_definition_list;
    struct aio_class_list *class_list;

} aio_core;

struct aio_value_list *inflate_aio_core(struct aio_bundle *input_bundle);

/**
 * Global core.
 */

extern struct aio_core *core;

#endif //AIO_CORE_H