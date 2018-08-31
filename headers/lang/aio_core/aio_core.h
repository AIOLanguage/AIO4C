#ifndef AIO_CORE_H
#define AIO_CORE_H

#include <lib/utils/str_hook/str_hook.h>

#define NUMBER_OF_CORE_TYPES 5

typedef struct aio_core {
    //Main:
    struct string_set *aio_type_set;
    struct string_list *source_code_list;
    //Data:
    struct aio_function_definition_list *global_function_definition_list;
    struct aio_field_definition_list *global_field_definition_list;
    struct aio_class_list *class_list;
    //Args:
    struct str_hook *root_function;
    struct aio_bundle *root_bundle;

} aio_core;

void inflate_aio_core();

void deflate_aio_core();

/**
 * Global core.
 */

extern struct aio_core *core;

#endif //AIO_CORE_H