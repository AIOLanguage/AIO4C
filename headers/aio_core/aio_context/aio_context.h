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

    /**
     * State.
     */

    enum aio_context_state context_state;

    /**
     * Breaks.
     */

    struct int_list *break_points;

    /**
     * Pressed source code.
     */

    struct string_builder *source_code_builder;

    /**
     * Real source code.
     */

    struct str_hook_list *source_code;

    /**
     * Context iterator.
     */

    struct str_hook_iterator *iterator;

    /**
     * Lexer nest.
     */

    struct aio_spider_nest *spider_nest;

    /**
     * Imported types.
     */

    struct str_hook_list *types;

    /**
     * Graph of interpret.
     */

    struct aio_context_control_graph *context_graph;

} aio_context;

struct aio_value_list *inflate_aio_context(struct aio_bundle *bundle);

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