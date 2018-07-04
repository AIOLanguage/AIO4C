#ifndef AIO_AIO_OBJECT_H
#define AIO_AIO_OBJECT_H

#include "../methods/bundle/aio_bundle.h"
#include "../../lib/collections/maps/aio_method_definition_map.h"

typedef struct aio_method_manager {
    aio_method_definition_map* method_definition_map;
} aio_method_manager;

aio_method_manager* new_aio_method_manager(aio_method_definition_map *method_definition_map);

typedef struct aio_file {
    const_string name;
    const_string folder_path;
    string_list* source_code;
    aio_method_manager* method_manager;
} aio_file;

aio_file* new_aio_file(aio_method_manager *method_manager, const_string path);

void invoke_method_in_manager(aio_file *object, const_string method_name, aio_bundle *bundle);

#endif //AIO_AIO_OBJECT_H