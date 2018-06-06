#include "../../../../headers/lang/object/objectManager/AIOObjectManager.h"

void initAIOObjectManager(AIOObjectManager** objectManager){
    *objectManager = malloc(sizeof(AIOObjectManager));
    AIOMutableObjectMap* objectMap;
    createMutableMapOfAIOObject(&objectMap);
    (*objectManager)->objectMap = objectMap;
    (*objectManager)->lastVisitedObject = malloc(sizeof(AIOObject));
}

/*
 * /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * initAIOObjectManager(&aioObjectManager);
 * printf("%d", *aioObjectManager->objectMap->size);
 */