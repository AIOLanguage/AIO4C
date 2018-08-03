#ifndef AIO_FILE_H
#define AIO_FILE_H

#include "../../lib/collections/maps/aio_function_definition_map.h"
#include "../../lib/utils/string_utils/string_utils.h"
#include "../../lib/collections/lists/string_list.h"
#include "../aio_function/aio_bundle/aio_bundle.h"

#define AIO_COMMENTS "//"

#define AIO_SUFFIX ".aio"

#define AIO_SUFFIX_LENGTH 4

typedef struct aio_function_manager {
    aio_function_definition_map *function_definition_map;
} aio_function_manager;

typedef struct aio_context {
    string name;
    string source_code;
    aio_function_manager *function_manager;
} aio_context;

aio_function_manager *new_aio_function_manager();

aio_context *new_aio_context(const_string path);

void invoke_function_in_context(aio_context *context, string function_name, aio_bundle *bundle);

#endif //AIO_FILE_H