#ifndef AIO_BUNDLE_H
#define AIO_BUNDLE_H

#include "../aio_value/aio_value.h"

typedef struct aio_bundle {
    struct aio_value_list *input_values;
    struct aio_value_list *output_values;
} aio_bundle;

struct aio_bundle *new_aio_bundle(struct aio_value_list *input_values);

void free_aio_bundle(struct aio_bundle *bundle);

/**
 * Typedef utils.
 */

typedef const aio_bundle const_aio_bundle;

#endif //AIO_BUNDLE_H