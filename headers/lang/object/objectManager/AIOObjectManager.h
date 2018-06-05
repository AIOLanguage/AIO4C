#ifndef AIO_AIO_OBJECT_MANAGER_H
#define AIO_AIO_OBJECT_MANAGER_H

#include "../AIOObject.h"
#include "../../../lib/AIOMutableObjectMap.h"

typedef struct AIOObjectManager {
    struct AIOObject lastVisitedObject;
    struct AIOMutableObjectMap objectMap;
} AIOObjectManager;

extern AIOObjectManager aioObjectManager;

void initAIOObjectManager();

#endif //AIO_AIO_OBJECT_MANAGER_H