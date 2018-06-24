#ifndef AIO_AIO_OBJECT_MANAGER_H
#define AIO_AIO_OBJECT_MANAGER_H

#include "../../../lib/collections/maps/AIOObjectMap.h"

typedef struct AIOObjectManager {
    AIOObjectMap* objectMap;
    int behaviour;
} AIOObjectManager;

extern AIOObjectManager* aio_object_manager;

void initAIOObjectManager(AIOObjectManager** objectManager);

void build_aio_object_and_put_in_object_manager(AIOObjectManager *objectManager, char *path);

int isDefaultBehaviour(AIOObjectManager* objectManager);

#endif //AIO_AIO_OBJECT_MANAGER_H