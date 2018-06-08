#ifndef AIO_AIO_OBJECT_H
#define AIO_AIO_OBJECT_H

#include "../methods/bundle/AIOBundle.h"
#include "../../lib/collections/maps/AIOMethodDefinitionMap.h"
#include "objectManager/AIOObjectManager.h"

typedef struct StringPair {
    char* objectName;
    char* folderPath;
} StringPair;

typedef struct AIOMethodManager {
    AIOMethodDefinitionMap* methodDefinitionMap;
    int* hasMain;
} AIOMethodManager;

void createAIOMethodManager(AIOMethodManager **methodManager, AIOMethodDefinitionMap *methodDefinitionMap);

typedef struct AIOObject {
    char* name;
    char* folderPath;
    struct StringList* sourceCode;
    struct AIOMethodManager* methodManager;
} AIOObject;

StringPair *extractNameAnfFolderPathFromPath(char *path);

void createAIOObject(AIOObject **object, AIOMethodManager* methodManager, char *path);

//void invokeMethodInManager(AIOObjectManager* objectManager, AIOObject* object, char* methodName, AIOBundle* bundle);

#endif //AIO_AIO_OBJECT_H