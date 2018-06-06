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












/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
//int main() {
//    //Create methodName:
//    char* methodName = "@main";
//    //Create declaration:
//    AIOMutableListOfString* args;
//    createMutableListOfString(&args);
//    printf("%d\n", *args->size);
//    AIODeclaration* declaration;
//    createAIODeclaration(&declaration, methodName, args);
//    printf("%s\n", declaration->methodName);
//    //Create annotation list:
//    AIOMutableListOfAnnotations* annotations;
//    createMutableListOfAnnotations(&annotations);
//    printf("%d\n", *annotations->size);
//    //Create source code:
//    AIOMutableListOfString* sourceCode;
//    createMutableListOfString(&sourceCode);
//    //Create method size type:
//    enum AIOMethodSizeType methodSizeType = DEFAULT;
//    AIOMethodDefinition *definition;
//    createAIOMethodDefinition(&definition, methodName, declaration, annotations, sourceCode, &methodSizeType);
//    printf("%s\n", definition->name);
//
//    //Create method definition map:
//    AIOMutableMethodDefinitionMap* methodDefinitionMap;
//    createMutableMapOfDefinitions(&methodDefinitionMap);
//
//    putInMutableMapOfDefinitions(methodDefinitionMap, definition);
//
//    AIOMethodDefinition* definition1;
//    createAIOMethodDefinition(&definition1, "def1", declaration, annotations, sourceCode, &methodSizeType);
//
//    putInMutableMapOfDefinitions(methodDefinitionMap, definition1);
//
//    AIOMethodDefinition* definition2;
//    createAIOMethodDefinition(&definition2, "def2", declaration, annotations, sourceCode, &methodSizeType);
//
//    putInMutableMapOfDefinitions(methodDefinitionMap, definition2);
//
//    //Create method manager:
//    AIOMethodManager* methodManager;
//    createAIOMethodManager(&methodManager, methodDefinitionMap);
//
//    //Create AIO object:
//    AIOObject* aioObject;
//    createAIOObject(&aioObject, methodManager, "starter");
//    printf("%s\n", aioObject->name);
//
//    //let's make get!
//    AIOMethodDefinition* aioMethodDefinition = getMethodDefinitionInMutableMapByName(methodDefinitionMap, "def1");
//    printf("%s", aioMethodDefinition->declaration->methodName);
//
//    return 0;
//}