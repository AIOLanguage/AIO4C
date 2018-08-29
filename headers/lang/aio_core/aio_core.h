#ifndef AIO_CORE_H
#define AIO_CORE_H

#define NUMBER_OF_CORE_TYPES 5

typedef struct aio_core {
    struct aio_context_list *core_context_list;
    struct string_set *aio_type_set; //유형 포함 (Keep types):
} aio_core;

void inflate_aio_core();

const struct aio_context *inflate_aio_context_and_put_in_core(const char* context_path);

void free_aio_core();

/**
 * Global core.
 */

extern struct aio_core *core;

#endif //AIO_CORE_H