#ifndef AIO_CONTEXT_H
#define AIO_CONTEXT_H

#include "../../lib/utils/string_utils/string_utils.h"
#include "../aio_function/aio_bundle/aio_bundle.h"
#include "../aio_function/aio_function_definition/aio_function_definition.h"
#include "../../lib/utils/str_hook/str_hook.h"

#define AIO_COMMENTS "//"

#define AIO_SUFFIX ".aio"

#define AIO_SUFFIX_LENGTH 4

/**
 * Static function manager.
 */

typedef struct aio_static_function_manager {
    struct aio_function_definition_list *definition_list;
} aio_static_function_manager;

/**
 * Context.
 */

typedef struct aio_context {
    const struct str_hook *name;
    const char *source_code;
    const struct aio_static_function_manager *function_manager;
} aio_context;

const struct aio_context *new_aio_context(const char *path);

void upbuild_aio_context(const struct aio_context *context);

void invoke_static_function_in_context(
        const struct aio_context *context,
        const struct str_hook *function_name,
        struct aio_bundle *bundle
);

void free_aio_context(const struct context *);

/**
 * List.
 */

typedef struct aio_context_list {
    unsigned int capacity;
    unsigned int size;
    const struct aio_context **contexts;
} aio_context_list;

struct aio_context_list *new_aio_context_list();

void add_aio_context_in_list(struct aio_context_list *list, const struct aio_context *context);

const struct aio_context *get_aio_context_in_list_by_name(const struct aio_context_list *list,
                                                          const struct str_hook *context_name);

void free_aio_context_list(struct aio_context_list *context_list);

/**
 * Typedef utils.
 */

typedef const aio_static_function_manager const_aio_static_function_manager;

typedef const aio_context const_aio_context;

typedef const aio_context **const_aio_context_array;

typedef const aio_context_list const_aio_context_list;

#endif //AIO_CONTEXT_H