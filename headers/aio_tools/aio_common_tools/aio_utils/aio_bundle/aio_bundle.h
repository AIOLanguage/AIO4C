#ifndef AIO_BUNDLE_H
#define AIO_BUNDLE_H

typedef struct aio_bundle {
    struct str_hook *path;
    struct str_hook *function_name;
    struct aio_value_list *input_values;
    struct aio_value_list *output_values;
} aio_bundle;

struct aio_bundle *new_aio_bundle(
        struct str_hook *path,
        struct str_hook *function_name,
        struct aio_value_list *input_values
);

void free_aio_bundle(struct aio_bundle *bundle);

/**
 * Typedef utils.
 */

typedef const aio_bundle const_aio_bundle;

#endif //AIO_BUNDLE_H