#include <mem.h>
#include <malloc.h>
#include <stdio.h>
#include "../../../headers/lang/object/AIOObject.h"

//Passed JUnitTest!
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

#define CHUNK 1024

//Path example:
//"../aioPrograms/test.txt", "r"
void loadSourceCodeInAIOObject(AIOObject *object, char *path) {
    //Create source code mutable list:
    AIOMutableListOfString *sourceCode;
    createMutableListOfString(&sourceCode);
    //Create file:
    FILE *file;
    //Create line buffer:
    char buffer[CHUNK];
    if ((file = fopen(path, "r")) == NULL) {
        perror("cannot open source-file");
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strlen(buffer) - 1] = '\0';
        //Create string:
        char *line = calloc(1, CHUNK);
        strcpy(line, buffer);
        //put string in list:
        addInMutableListOfString(sourceCode, line);
    }
    fclose(file);
    //Set source code:
    object->sourceCode = sourceCode;
}

void findMethodsInManager(AIOMethodManager *methodManager) {

}

//Passed JUnitTest!
void createAIOObject(AIOObject **object, AIOMethodManager *methodManager, char *path) {
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



/*
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CHUNK 1024

int main() {
    AIOMutableListOfString* sourceCode;
    createMutableListOfString(&sourceCode);
    FILE *file;
    char buffer[CHUNK];
    if ((file = fopen("../aioPrograms/test.aio", "r")) == NULL) {
        perror("cannot open source-file");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strlen(buffer) - 1] = '\0';
        printf("%d\n", strlen(buffer));
        char *line = calloc(1, CHUNK);
        strcpy(line, buffer);
        addInMutableListOfString(sourceCode, line);
    }
    fclose(file);
    for (int i = 0; i < *sourceCode->size; ++i) {
        printf("%s\n", sourceCode->strings[i]);
    }
    printf("4 line: %s\n", getStringInMutableListByIndex(sourceCode, 4));
    return 0;
}
 */
