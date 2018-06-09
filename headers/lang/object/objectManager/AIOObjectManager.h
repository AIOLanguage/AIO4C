#ifndef AIO_AIO_OBJECT_MANAGER_H
#define AIO_AIO_OBJECT_MANAGER_H

#include "../../../lib/collections/maps/AIOObjectMap.h"

typedef struct AIOObjectManager {
    AIOObjectMap* objectMap;
    AIOObject* lastVisitedObject;
    int behaviour;
} AIOObjectManager;

extern AIOObjectManager* aioObjectManager;

void initAIOObjectManager(AIOObjectManager** objectManager);

void buildAIOObjectAndPutInAIOObjectManager(AIOObjectManager *objectManager, char *path);

int isDefaultBehaviour(AIOObjectManager* objectManager);

#endif //AIO_AIO_OBJECT_MANAGER_H