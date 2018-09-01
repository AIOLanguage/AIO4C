#ifndef AIO_CONTEXT_H
#define AIO_CONTEXT_H

/**
 * Context state.
 */

typedef enum aio_context_state {
    AIO_CONTEXT_IS_ABSENT, AIO_CONTEXT_IS_LOADING, AIO_CONTEXT_IS_READY
} aio_context_state;

/**
 * Context.
 */

typedef struct aio_context {
    enum aio_context_state context_state;
    struct int_list* break_points;
    struct string_builder *source_code_builder;
} aio_context;

void inflate_aio_context(struct aio_bundle *bundle);

/**
 * List.
 */

typedef struct aio_context_list {
    unsigned capacity;
    unsigned size;
    struct str_hook *source_paths;
    struct aio_context **contexts;
} aio_context_list;

struct aio_context_list *new_aio_context_list();

#endif //AIO_CONTEXT_H