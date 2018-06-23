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
                            perror("incorrect method name @");
                        }
                        break;
                    }
                    nameSize = nameSize + 1;
                }
                char *methodName = calloc(nameSize + 1, sizeof(char));
                for (int k = 0; k < nameSize; ++k) {
                    methodName[k] = line[k];
                }
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
    createStringList(&sourceCode);
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
        addInStringList(sourceCode, line);
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