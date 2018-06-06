#ifndef AIO_AIO_OBJECT_H
#define AIO_AIO_OBJECT_H

#include "../methods/bundle/AIOBundle.h"
#include "../../lib/collections/maps/AIOMutableMethodDefinitionMap.h"

typedef struct AIOMethodManager {
    AIOMutableMethodDefinitionMap* methodDefinitionMap;
    int* hasMain;
} AIOMethodManager;

void createAIOMethodManager(AIOMethodManager **methodManager, AIOMutableMethodDefinitionMap *methodDefinitionMap);

typedef struct AIOObject {
    char* name;
    char* folderPath;
    struct AIOMutableListOfString* sourceCode;
    struct AIOMethodManager* methodManager;
} AIOObject;

void createAIOObject(AIOObject **object, AIOMethodManager* methodManager, char *path);

void invokeMethodInManager(struct AIOMethodManager methodManager, char methodName[], struct AIOBundle bundle);

#endif //AIO_AIO_OBJECT_H