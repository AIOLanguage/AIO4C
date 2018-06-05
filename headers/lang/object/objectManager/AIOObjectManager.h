#ifndef AIO_AIO_OBJECT_MANAGER_H
#define AIO_AIO_OBJECT_MANAGER_H

#include "../AIOObject.h"
#include "../../../lib/maps/AIOMutableObjectMap.h"

typedef struct AIOObjectManager {
    AIOObject* lastVisitedObject;
    AIOMutableObjectMap* objectMap;
} AIOObjectManager;

extern AIOObjectManager aioObjectManager;

void initAIOObjectManager();

#endif //AIO_AIO_OBJECT_MANAGER_H