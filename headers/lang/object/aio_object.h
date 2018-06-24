#ifndef AIO_AIO_OBJECT_H
#define AIO_AIO_OBJECT_H

#include "../methods/bundle/aio_bundle.h"
#include "../../lib/collections/maps/aio_method_definition_map.h"

typedef struct aio_method_manager {
    aio_method_definition_map* method_definition_map;
    int hasMain;
} aio_method_manager;

aio_method_manager* new_aio_method_manager(aio_method_definition_map *method_definition_map);

typedef struct aio_object {
    char* name;
    char* folder_path;
    struct string_list* source_code;
    struct aio_method_manager* method_manager;
} aio_object;

aio_object* new_aio_object(aio_method_manager *method_manager, char *path);

void invoke_method_in_manager(aio_object *object, char *method_name, aio_bundle *bundle);

#endif //AIO_AIO_OBJECT_H