#ifndef AIO_AIO_OBJECT_MANAGER_H
#define AIO_AIO_OBJECT_MANAGER_H

#include "../../../lib/collections/maps/aio_object_map.h"

typedef struct aio_object_manager {
    aio_object_map *objectMap;
    int behaviour;
} aio_object_manager;

extern aio_object_manager *object_manager;

aio_object_manager *init_aio_object_manager();

void build_aio_object_and_put_in_object_manager(aio_object_manager *objectManager, char *path);

int is_default_behaviour(aio_object_manager *object_manager);

#endif //AIO_AIO_OBJECT_MANAGER_H