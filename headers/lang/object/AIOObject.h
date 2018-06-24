#ifndef AIO_AIO_OBJECT_H
#define AIO_AIO_OBJECT_H

#include "../methods/bundle/aio_bundle.h"
#include "../../lib/collections/maps/AIOMethodDefinitionMap.h"

typedef struct AIOMethodManager {
    AIOMethodDefinitionMap* methodDefinitionMap;
    int* hasMain;
} AIOMethodManager;

void createAIOMethodManager(AIOMethodManager **methodManager, AIOMethodDefinitionMap *methodDefinitionMap);

typedef struct AIOObject {
    char* name;
    char* folderPath;
    struct string_list* sourceCode;
    struct AIOMethodManager* methodManager;
} aio_object;

void createAIOObject(aio_object **object, AIOMethodManager* methodManager, char *path);

void invokeMethodInManager(aio_object* object, char* methodName, aio_bundle* bundle);

#endif //AIO_AIO_OBJECT_H