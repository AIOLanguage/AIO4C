#include <mem.h>
#include <malloc.h>
#include "../../../headers/lang/object/AIOObject.h"

char *extractAIONameFromPath(char *path) {
    return path;
}

char *extractAIOFolderFromPath(char *path) {
    return path;
}

void loadSourceCodeInAIOObject(AIOObject* object, char* path) {

}

void findMethodsInManager(AIOMethodManager* methodManager) {

}

void createAIOObject(AIOObject* object, char *path) {
    object = malloc(sizeof(AIOObject));
    //Extract aio object name:
    strcpy(object->name, extractAIONameFromPath(path));
    //Extract folder path:
    strcpy(object->folderName, extractAIOFolderFromPath(path));
    //Loading code:
    loadSourceCodeInAIOObject(object, path);
    //Create method manager:
    AIOMethodManager* methodManager = malloc(sizeof(AIOMethodManager));


    //    struct AIOMethodManager methodManager = {.methodDefinitionMap = mutableMapOfDefinitions()};
  //  findMethodsInManager(methodManager);
}

void invokeMethodInManager(struct AIOMethodManager methodManager, char methodName[], struct AIOBundle bundle) {

}