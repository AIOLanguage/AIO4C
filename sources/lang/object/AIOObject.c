#include <mem.h>
#include <malloc.h>
#include <stdio.h>
#include <process.h>
#include "../../../headers/lang/object/objectManager/AIOObjectManager.h"
#include "../../../headers/lang/methods/methodDefinition/AIOMethodDefinitionBuilder.h"
#include "../../../headers/lang/methods/AIOMethod.h"
#include "../../../headers/lib/utils/fileUtils/FileUtils.h"

AIOObjectManager *aioObjectManager;

//Passed JUnitTest!
void createAIOMethodManager(AIOMethodManager **methodManager, AIOMethodDefinitionMap *methodDefinitionMap) {
    //Create the same method manager:
    *methodManager = calloc(1, sizeof(AIOMethodManager));
    if (*methodManager == NULL) {
        perror("cannot allocate memory for aio method manager!");
        exit(1);
    }
    //Set method definition map:
    (*methodManager)->methodDefinitionMap = methodDefinitionMap;
    //Set boolean "has main": (default false)
    (*methodManager)->hasMain = calloc(1, sizeof(int));
    if ((*methodManager)->hasMain == NULL) {
        perror("cannot allocate memory for hasMain property in aio method manager!");
        exit(1);
    }
    *(*methodManager)->hasMain = -1;
}

//Passed JUnitTest!
void findMethodsInManager(AIOObject *aioObject) {
    for (int i = 0; i < *aioObject->sourceCode->size; ++i) {
        char *line = aioObject->sourceCode->strings[i];
        int length = strlen(line);
        if (length > 1) {
            //starts with @
            if (line[0] == '@') {
                unsigned nameSize = 1;
                char pointer;
                for (int j = 1; j < length; ++j) {
                    if (line[j] == ' ') {
                        if (j == 1) {
                            perror("incorrect method mane @");
                        }
                        break;
                    }
                    nameSize = nameSize + 1;
                }
                char *methodName = calloc(nameSize + 1, sizeof(char));
                for (int k = 0; k < nameSize; ++k) {
                    methodName[k] = line[k];
                }
                free(&nameSize);
                free(&pointer);
                if (strcmp(methodName, "@main") == 0) {
                    *aioObject->methodManager->hasMain = 0;
                    printf("HAS MAIN: %d\n", *aioObject->methodManager->hasMain);
                }
                AIOMethodDefinition *methodDefinition = buildAIOMethodDefinition(methodName, aioObject->sourceCode, i);
                putAIOMethodDefinitionInMap(aioObject->methodManager->methodDefinitionMap, methodDefinition);
            }
        }
    }
}

#define CHUNK 1024

//Path example:
//"../aioPrograms/test.txt", "r"
//Passed JUnitTest!
void loadSourceCodeInAIOObject(AIOObject *object, char *path) {
    printf("Loading source code...\n");
    //Create source code mutable list:
    StringList *sourceCode;
    createListOfString(&sourceCode);
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
        addInListOfString(sourceCode, line);
    }
    fclose(file);
    //Set source code:
    object->sourceCode = sourceCode;
}

//Passed JUnitTest!
void createAIOObject(AIOObject **object, AIOMethodManager *methodManager, char *path) {
    //Create the same object:
    *object = malloc(sizeof(AIOObject));
    //Set method manager:
    (*object)->methodManager = methodManager;
    //Set name from path:
    StringPair *nameVsFolder = extractNameAndFolderPathFromPath(path);
    (*object)->name = nameVsFolder->first;
    //Set folder path from path:
    (*object)->folderPath = nameVsFolder->second;
    //Loading code:
    loadSourceCodeInAIOObject(*object, path);
    findMethodsInManager(*object);
}

void invokeMethodInManager(AIOObject *object, char *methodName, AIOBundle *bundle) {
    AIOMethodDefinition *methodDefinition = getAIOMethodDefinitionInMapByName(
            object->methodManager->methodDefinitionMap, methodName);
    if (methodDefinition->declaration != NULL) {
        if (*methodDefinition->declaration->argList->size != *bundle->inputValues->size) {
            perror("number of args not matches with arg size of declaration!");
        }
    }
    AIOMethod *method;
    createAIOMethodAndInvoke(object, &method, methodDefinition, bundle);
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
//int main() {
//    //Create methodName:
//    char* methodName = "@main";
//    //Create declaration:
//    StringList* args;
//    createListOfString(&args);
//    printf("%d\n", *args->size);
//    AIODeclaration* declaration;
//    createAIODeclaration(&declaration, methodName, args);
//    printf("%s\n", declaration->methodName);
//    //Create annotation list:
//    AIOAnnotationList* annotations;
//    createAnnotationList(&annotations);
//    printf("%d\n", *annotations->size);
//    //Create source code:
//    StringList* sourceCode;
//    createListOfString(&sourceCode);
//    //Create method size type:
//    enum AIOMethodSizeType methodSizeType = DEFAULT;
//    AIOMethodDefinition *definition;
//    createAIOMethodDefinition(&definition, methodName, declaration, annotations, sourceCode, &methodSizeType);
//    printf("%s\n", definition->name);
//
//    //Create method definition map:
//    AIOMethodDefinitionMap* methodDefinitionMap;
//    createAIOMethodDefinitionMap(&methodDefinitionMap);
//
//    putAIOMethodDefinitionInMap(methodDefinitionMap, definition);
//
//    AIOMethodDefinition* definition1;
//    createAIOMethodDefinition(&definition1, "def1", declaration, annotations, sourceCode, &methodSizeType);
//
//    putAIOMethodDefinitionInMap(methodDefinitionMap, definition1);
//
//    AIOMethodDefinition* definition2;
//    createAIOMethodDefinition(&definition2, "def2", declaration, annotations, sourceCode, &methodSizeType);
//
//    putAIOMethodDefinitionInMap(methodDefinitionMap, definition2);
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
//    AIOMethodDefinition* aioMethodDefinition = getAIOMethodDefinitionInMapByName(methodDefinitionMap, "def1");
//    printf("%s", aioMethodDefinition->declaration->methodName);
//
//    return 0;
//}

/*
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CHUNK 1024

int main() {
    StringList* sourceCode;
    createListOfString(&sourceCode);
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
        addInListOfString(sourceCode, line);
    }
    fclose(file);
    for (int i = 0; i < *sourceCode->size; ++i) {
        printf("%s\n", sourceCode->strings[i]);
    }
    printf("4 line: %s\n", getStringInListByIndex(sourceCode, 4));
    return 0;
}
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 */

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * char* path = "../aioPrograms/starter.aio";
    StringPair* stringPair = extractNameAndFolderPathFromPath(path);
    char* first = stringPair->first;
    char* second = stringPair->second;
    printf("NAME: %s\n", first);
    printf("FOLDER: %s\n", second);
 */
