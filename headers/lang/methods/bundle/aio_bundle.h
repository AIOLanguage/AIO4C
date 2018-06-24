#ifndef AIO_AIO_BUNDLE_H
#define AIO_AIO_BUNDLE_H

#include "../../../lib/collections/lists/string_list.h"

typedef struct aio_bundle {
    string_list *input_values;
    string_list *output_values;
} aio_bundle;

aio_bundle *new_aio_bundle(string_list *input_values);

#endif //AIO_AIO_BUNDLE_H