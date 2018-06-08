#ifndef AIO_AIO_OBJECT_MANAGER_H
#define AIO_AIO_OBJECT_MANAGER_H

#include "../AIOObject.h"
#include "../../../lib/collections/maps/AIOObjectMap.h"

typedef struct AIOObjectManager {
    AIOObject* lastVisitedObject;
    AIOObjectMap* objectMap;
    int behaviour;
} AIOObjectManager;

extern AIOObjectManager* aioObjectManager;

void initAIOObjectManager(AIOObjectManager** objectManager);

void buildAIOObjectAndPutInAIOObjectManager(AIOObjectManager *objectManager, char *path);

int isDefaultBehaviour(AIOObjectManager* objectManager);

#endif //AIO_AIO_OBJECT_MANAGER_H