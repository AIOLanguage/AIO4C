#ifndef AIO_FILE_H
#define AIO_FILE_H

#include "../../lib/collections/maps/aio_method_definition_map.h"
#include "../../lib/utils/string_utils/string_utils.h"
#include "../../lib/collections/lists/string_list.h"
#include "../aio_method/bundle/aio_bundle.h"

#define AIO_COMMENTS "//"

#define AIO_SUFFIX ".aio"

#define AIO_SUFFIX_LENGTH 4

typedef struct aio_method_manager {
    aio_method_definition_map *method_definition_map;
} aio_method_manager;

aio_method_manager *new_aio_method_manager();

typedef struct aio_context {
    const_string name;
    string_list *source_code;
    aio_method_manager *method_manager;
} aio_context;

aio_context *new_aio_context(const_string path);

void invoke_method_in_manager(aio_context *context, const_string method_name, aio_bundle *bundle);

#endif //AIO_FILE_H