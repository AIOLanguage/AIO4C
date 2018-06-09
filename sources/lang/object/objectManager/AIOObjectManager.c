#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lang/object/objectManager/AIOObjectManager.h"

//Passed JUnitTest!
void initAIOObjectManager(AIOObjectManager **objectManager) {
    *objectManager = calloc(1, sizeof(AIOObjectManager));
    if (*objectManager == NULL) {
        perror("cannot create AIOObjectManager");
        exit(1);
    }
    AIOObjectMap *objectMap;
    createAIOObjectMap(&objectMap);
    (*objectManager)->objectMap = objectMap;
    //Set default behaviour:
    (*objectManager)->behaviour = 0;
}

void buildAIOObjectAndPutInAIOObjectManager(AIOObjectManager *objectManager, char *path) {
    //Init aio object:
    AIOObject *aioObject;
    //Init aio method manager for aio object:
    AIOMethodManager *methodManager;
    //Create definition map for aio method manager:
    AIOMethodDefinitionMap *methodDefinitionMap;
    createAIOMethodDefinitionMap(&methodDefinitionMap);
    //Create aio method manager:
    createAIOMethodManager(&methodManager, methodDefinitionMap);
    //Create aio object:
    createAIOObject(&aioObject, methodManager, path);
    //Put new aio object in aio object manager map:
    putAIOObjectInMap(objectManager->objectMap, aioObject);
}

int isDefaultBehaviour(AIOObjectManager* objectManager) {
    return objectManager->behaviour;
}

/*
 * /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * initAIOObjectManager(&aioObjectManager);
 * printf("%d", *aioObjectManager->objectMap->size);
 */