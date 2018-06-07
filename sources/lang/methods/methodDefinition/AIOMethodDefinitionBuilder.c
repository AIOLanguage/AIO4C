#include <mem.h>
#include <stdio.h>
#include <ctype.h>
#include "../../../../headers/lang/methods/methodDefinition/AIOMethodDefinition.h"
#include "../../../../headers/lib/utils/StringUtils.h"

//Passed JUnitTest!
StringList *getSourceCodeOfMethod(char *methodName, StringList *sourceCode, int startIndex) {
    StringList *methodCode;
    createListOfString(&methodCode);
    int currentIndex = startIndex;
    char *trimmedLine = malloc(strlen(sourceCode->strings[currentIndex]));
    trim(sourceCode->strings[currentIndex], &trimmedLine);
    if (strcmp(trimmedLine, "") != 0) {
        char *cleanFirstLine = malloc(strlen(trimmedLine));
        int result = removePrefix(trimmedLine, methodName, &cleanFirstLine);
        if (result != 0) {
            addInListOfString(methodCode, cleanFirstLine);
        }
        while (++currentIndex < *sourceCode->size) {
            trimmedLine = malloc(strlen(sourceCode->strings[currentIndex]));
            trim(sourceCode->strings[currentIndex], &trimmedLine);
            if (strcmp(trimmedLine, "") == 0) {
                break;
            } else {
                addInListOfString(methodCode, trimmedLine);
            }
        }
    }
    return methodCode;
}

//While empty method:
AIOAnnotationList *getAnnotationsOfMethod(char *name, StringList *sourceCode, int startIndex) {
    AIOAnnotationList *annotations;
    createAnnotationList(&annotations);
    return annotations;
}

int isCorrectPlacedBrackets(char *line) {
    int length = strlen(line);
    for (int i = 0; i < length; ++i) {
        if ((i == 0 || i == 1 || i == length - 2 || i == length - 1) && line[i] != '<') {
            return -1;
        }
        if (i >= 2 && i <= length - 3 && line[i] == '<') {
            return -1;
        }
    }
    return 0;
}

StringList *getArgsIfCorrect(char *argLine) {
    char **splitArgsByComma;
    splitByChar(argLine, ',', &splitArgsByComma);
    StringList *argList;
    createListOfString(&argList);
    for (int i = 0; i < _msize(splitArgsByComma) / 4; ++i) {
        char *trimmedLine = malloc(strlen(splitArgsByComma[i]));
        if (trimmedLine == NULL) {
            perror("cannot allocate memory for trimmed line for arg in declaration!");
        }
        trim(splitArgsByComma[i], &trimmedLine);
        addInListOfString(argList, trimmedLine);
    }
    for (int j = 0; j < *argList->size; ++j) {
        if (isWord(getStringInListByIndex(argList, j)) == -1) {
            perror("arg in declaration has invalid name!");
        }
    }
    return argList;
}

AIODeclaration *getDeclarationOfMethod(char *methodName, StringList *sourceCode, int startIndex) {
    int currentIndex = startIndex - 1;
    char *inputLine = getStringInListByIndex(sourceCode, currentIndex);
    printf("Allocate memory for current line...");
    char *currentLine = malloc(strlen(inputLine));
    if (currentLine == NULL) {
        perror("cannot allocate memory for current line when was creating of declaration!");
    }
    trim(inputLine, &currentLine);
    printf("TRIMMED FIRST LINE: %s\n", currentLine);
    while (strcmp(currentLine, "") != 0 && currentIndex >= 0) {
        char *declarationPrefix = "~dec:";
        int startsAsDeclaration = startsWith(currentLine, declarationPrefix);
        if (startsAsDeclaration == 0) {
            printf("FOUND DECLARATION!");
            //Remove declaration prefix:
            char *bracketLine = malloc(strlen(currentLine));
            if (bracketLine == NULL){
                perror("cannot allocate memory for bracket line when was creating of declaration!");
            }
            removePrefix(currentLine, declarationPrefix, &bracketLine);
            printf("BRACKET LINE: %s\n", bracketLine);
            //<<w+<<:
            if (strlen(bracketLine) > 4 && isCorrectPlacedBrackets(bracketLine) == 0) {
                //Remove brackets:
                printf("REMOVING BRACKETS...\n");
                char *lp = malloc(strlen(bracketLine));
                if (lp == NULL){
                    perror("cannot allocate memory for left padding when was creating of declaration!");
                }
                removePrefix(bracketLine, "<<", &lp);
                printf("LINE WITHOUT LP: %s\n", lp);
                char *rp = malloc(strlen(lp));
                if (rp == NULL){
                    perror("cannot allocate memory for right padding when was creating of declaration!");
                }
                removeSuffix(lp, "<<", &rp);
                printf("LINE WITHOUT RP: %s\n", rp);
                //Split naked args;
                printf("PREPARE TO SPLIT...\n");
                char **dirtySplitArgs;
                splitByChar(rp, ' ', &dirtySplitArgs);
                printf("PREPARE TO SPLIT...\n");

                int argNumber = _msize(dirtySplitArgs) / 4;
                char **filteredArgs = calloc(_msize(dirtySplitArgs) / 4, sizeof(char *));
                filter(dirtySplitArgs, (size_t) argNumber, &filteredArgs, isNotEmpty);
                char *cleanArgLine;
                joinToStringWithoutSpaces(filteredArgs, &cleanArgLine);
                StringList *argList = getArgsIfCorrect(cleanArgLine);
                if (isStringListEmpty(argList) != 0) {
                    AIODeclaration *aioDeclaration;
                    createAIODeclaration(&aioDeclaration, methodName, argList);
                } else {
                    perror("invalid comma placement in declaration!");
                }
            } else {
                perror("invalid bracket placement in declaration!");
            }
        } else {
            currentLine = getStringInListByIndex(sourceCode, --currentIndex);
        }
    }
    return NULL;
}


//Passed JUnitTest!
int isDefaultOperations(const char *operation) {
    if (strlen(operation) == 1) {
        if (operation[0] == '+' || operation[0] == '*' || operation[0] == '&') {
            return 0;
        }
    }
    return -1;
}

//Passed JUnitTest!
int isTheShortestInTheSameObject(const char *operation) {
    int length = strlen(operation);
    //w+~
    if (length > 1) {
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

//Passed JUnitTest!
int isTheShortestInTheOtherObject(const char *operation) {
    int length = strlen(operation);
    //w+.@w+~
    if (length > 4) {
        //first is letter and ends with ~:
        if (isalpha(operation[0]) && operation[length - 1] == '~') {
            int wasDelimiter = -1;
            int startMethodNameIndex = 0;
            for (int i = 1; i < length - 1; ++i) {
                //across with dot:
                if (operation[i] == '.') {
                    //.@w+
                    if (i + 2 < length - 1 && operation[i + 1] == '@') {
                        wasDelimiter = 0;
                        startMethodNameIndex = i + 2;
                        break;
                    } else {
                        perror("illegal aio line with method invocation");
                    }
                } else if (!isalnum(operation[i])) {
                    return -1;
                }
            }
            if (wasDelimiter == 0) {
                for (int i = startMethodNameIndex; i < length - 1; ++i) {
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

AIOMethodDefinition *buildAIOMethodDefinition(char *methodName, StringList *sourceCode, int startIndex) {
    //Create the same method definition:
    AIOMethodDefinition *methodDefinition = calloc(1, sizeof(AIOMethodDefinition));
    StringList *methodCode = getSourceCodeOfMethod(methodName, sourceCode, startIndex);
    //Check source code:
    for (int i = 0; i < *methodCode->size; ++i) {
        printf("%s\n", getStringInListByIndex(methodCode, i));
    }
    printf("\n\n\n\n\n\n\n");
    printf("Create AIODeclaration...\n");
    AIODeclaration *aioDeclaration = getDeclarationOfMethod(methodName, sourceCode, startIndex);
    printf("Create AIOAnnotation list...\n");
    AIOAnnotationList *aioAnnotationList = getAnnotationsOfMethod(methodName, sourceCode, startIndex);
    printf("Successfully created method definition!\n");
    return methodDefinition;
}