#include <mem.h>
#include <stdio.h>
#include "../../../../headers/lang/methods/methodDefinition/AIOMethodDefinition.h"
#include "../../../../headers/lib/utils/StringUtils.h"

AIOMutableListOfString *getSourceCodeOfMethod(char *methodName, AIOMutableListOfString *sourceCode, int startIndex) {
    AIOMutableListOfString *methodCode;
    createMutableListOfString(&methodCode);
    int currentIndex = startIndex;
    char *trimmedLine = malloc(strlen(sourceCode->strings[currentIndex]));
    trim(sourceCode->strings[currentIndex], &trimmedLine);
    if (strcmp(trimmedLine, "") != 0) {
        char *cleanFirstLine = malloc(strlen(trimmedLine));
        int result = removePrefix(trimmedLine, methodName, &cleanFirstLine);
        if (result != 0) {
            addInMutableListOfString(methodCode, cleanFirstLine);
        }
        while (++currentIndex < *sourceCode->size) {
            trimmedLine = malloc(strlen(sourceCode->strings[currentIndex]));
            trim(sourceCode->strings[currentIndex], &trimmedLine);
            if (strcmp(trimmedLine, "") == 0) {
                break;
            } else {
                addInMutableListOfString(methodCode, trimmedLine);
            }
        }
    }
    return methodCode;
}

AIOMethodDefinition *buildAIOMethodDefinition(char *methodName, AIOMutableListOfString *sourceCode, int startIndex) {
    //Create the same method definition:
    AIOMethodDefinition *methodDefinition = calloc(1, sizeof(AIOMethodDefinition));
    AIOMutableListOfString *methodCode = getSourceCodeOfMethod(methodName, sourceCode, startIndex);
    for (int i = 0; i < *methodCode->size; ++i) {
        printf("%s\n", getStringInMutableListByIndex(methodCode, i));
    }
    return methodDefinition;
}