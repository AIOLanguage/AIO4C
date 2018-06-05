#include <mem.h>
#include <malloc.h>
#include "../../../headers/lang/object/AIOObject.h"

void createAIOMethodManager(AIOMethodManager **methodManager, AIOMutableMethodDefinitionMap *methodDefinitionMap) {
    //Create the same method manager:
    *methodManager = malloc(sizeof(AIOMethodManager));
    //Set method definition map:
    (*methodManager)->methodDefinitionMap = methodDefinitionMap;
    //Set boolean "has main": (default false)
    (*methodManager)->hasMain = malloc(sizeof(int));
    *(*methodManager)->hasMain = -1;
}

char *extractAIONameFromPath(char *path) {
    return path;
}

char *extractAIOFolderPathFromPath(char *path) {
    return path;
}

void loadSourceCodeInAIOObject(AIOObject *object, char *path) {

}

void findMethodsInManager(AIOMethodManager *methodManager) {

}

void createAIOObject(AIOObject **object, AIOMethodManager* methodManager, char *path) {
    //Create the same object:
    *object = malloc(sizeof(AIOObject));
    //Set method manager:
    (*object)->methodManager = methodManager;
    //Set name from path:
    (*object)->name = extractAIONameFromPath(path);
    //Set folder path from path:
    (*object)->folderPath = extractAIOFolderPathFromPath(path);
    //Loading code:
    loadSourceCodeInAIOObject(*object, path);
    findMethodsInManager(methodManager);
}

void invokeMethodInManager(struct AIOMethodManager methodManager, char methodName[], struct AIOBundle bundle) {

}