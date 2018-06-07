#include <mem.h>
#include <stdio.h>
#include <ctype.h>
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

//While empty method:
AIOMutableListOfAnnotations *getAnnotationsOfMethod(char *name, AIOMutableListOfString *sourceCode, int startIndex) {
    AIOMutableListOfAnnotations* annotations;
    createMutableListOfAnnotations(&annotations);
    return annotations;
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

int isDefaultOperations(const char *operation) {
    if (strlen(operation) > 0) {
        if (operation[0] == '+' || operation[0] == '*' || operation[0] == '&') {
            return 0;
        }
    }
    return -1;
}

int isTheShortestInTheSameObject(const char *operation) {
    int length = strlen(operation);
    if (length > 0) {
        if (isalpha(operation[0]) && operation[length - 1] == '~') {
            for (int i = 1; i < length - 1; ++i) {
                if (!isalnum(operation[i])) {
                    return -1;
                }
            }
            return 0;
        }
    }
    return -1;
}

int isTheShortestInTheOtherObject(const char *operation) {
    int length = strlen(operation);
    if (length > 0) {
        if (isalpha(operation[0]) && operation[length - 1] == '~') {
            int wasDelimiter = -1;
            int startMethodNameIndex = 0;
            for (int i = 1; i < length - 1; ++i) {
                if (operation[i] == '.') {
                    //.@*
                    if (i + 2 < length && operation[i + 1] == '@') {
                        wasDelimiter = 0;
                        startMethodNameIndex = i + 2;
                        break;
                    } else {
                        perror("illegal aio line with method invocation");
                    }
                }
                if (!isalnum(operation[i])) {
                    return -1;
                }
            }
            if (wasDelimiter == 0) {
                for (int i = startMethodNameIndex; i < length; ++i) {
                    if (!isalnum(operation[i])) {
                        return -1;
                    }
                }
                return 0;
            } else {
                return -1;
            }
        }
    }
    return -1;
}