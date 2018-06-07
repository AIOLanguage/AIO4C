#ifndef AIO_AIO_OBJECT_MANAGER_H
#define AIO_AIO_OBJECT_MANAGER_H

#include "../AIOObject.h"
#include "../../../lib/collections/maps/AIOObjectMap.h"

typedef struct AIOObjectManager {
    AIOObject* lastVisitedObject;
    AIOObjectMap* objectMap;
} AIOObjectManager;

extern AIOObjectManager* aioObjectManager;

void initAIOObjectManager(AIOObjectManager** objectManager);

void buildAIOObjectAndPutInAIOObjectManager(AIOObjectManager *objectManager, char *path);

#endif //AIO_AIO_OBJECT_MANAGER_H