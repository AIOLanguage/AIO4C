#include <mem.h>
#include <stdio.h>
#include <ctype.h>
#include <process.h>
#include "../../../../headers/lang/methods/methodDefinition/AIOMethodDefinition.h"
#include "../../../../headers/lib/utils/stringUtils/string_utils.h"
#include "../../../../headers/lang/object/objectManager/AIOObjectManager.h"
#include "../../../../headers/lib/utils/operationUtils/OperationUtils.h"

AIOObjectManager* aioObjectManager;

//Passed JUnitTest!
StringList *getSourceCodeOfMethod(char *methodName, StringList *sourceCode, int startIndex) {
    StringList *methodCode;
    createStringList(&methodCode);
    int currentIndex = startIndex;
    char *trimmedLine;
    trim(sourceCode->strings[currentIndex], &trimmedLine);
    if (strcmp(trimmedLine, "") != 0) {
        char *cleanFirstLine = calloc(strlen(trimmedLine) + 1, sizeof(char));
        if (cleanFirstLine == NULL) {
            perror("can not allocate memory for clean first line in during get source code method procedure performs!");
        }
        remove_prefix(trimmedLine, methodName, &cleanFirstLine);
        if (strcmp(cleanFirstLine, "") != 0) {
            addInStringList(methodCode, cleanFirstLine);
        }
        while (++currentIndex < *sourceCode->size) {
            char* currentLine;
            trim(sourceCode->strings[currentIndex], &currentLine);
            if (strcmp(currentLine, "") == 0) {
                break;
            } else {
                addInStringList(methodCode, currentLine);
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

//Passed JUnitTest!
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

//Passed JUnitTest!
StringList *getArgsIfCorrect(char **args) {
    StringList *argList;
    createStringList(&argList);
    for (int j = 0; j < _msize(args) / 4; ++j) {
        if (is_word(args[j]) == -1) {
            perror("arg in declaration has invalid name!");
            exit(1);
        } else {
            addInStringList(argList, args[j]);
        }
    }
    return argList;
}

//Passed JUnitTest!
AIODeclaration *getDeclarationOfMethod(char *methodName, StringList *sourceCode, int startIndex) {
    int currentIndex = startIndex - 1;
    char *inputLine = getStringInListByIndex(sourceCode, currentIndex);
    char *currentLine;
    trim(inputLine, &currentLine);
    while (strcmp(currentLine, "") != 0 && currentIndex >= 0) {
        char *declarationPrefix = "~dec:";
        int startsAsDeclaration = starts_with(currentLine, declarationPrefix);
        if (startsAsDeclaration == 0) {
            //Remove declaration prefix:
            char *bracketLine = malloc(strlen(currentLine));
            if (bracketLine == NULL) {
                perror("cannot allocate memory for bracket line when was creating of declaration!");
                exit(1);
            }
            remove_prefix(currentLine, declarationPrefix, &bracketLine);
            //<<w+<<:
            if (strlen(bracketLine) > 4 && isCorrectPlacedBrackets(bracketLine) == 0) {
                //Remove brackets:
                char *lp = malloc(strlen(bracketLine));
                if (lp == NULL) {
                    perror("cannot allocate memory for left padding when was creating of declaration!");
                    exit(1);
                }
                remove_prefix(bracketLine, "<<", &lp);
                char *rp = malloc(strlen(lp));
                if (rp == NULL) {
                    perror("cannot allocate memory for right padding when was creating of declaration!");
                    exit(1);
                }
                remove_suffix(lp, "<<", &rp);
                //Split naked args;
                char **dirtySplitArgs;
                split_by_char(rp, ',', &dirtySplitArgs);
                //Trim all args:
                char **args;
                trim_all(dirtySplitArgs, _msize(dirtySplitArgs) / 4, &args);
                StringList *argList = getArgsIfCorrect(args);
                AIODeclaration *aioDeclaration;
                createAIODeclaration(&aioDeclaration, methodName, argList);
                return aioDeclaration;
            } else {
                perror("invalid bracket placement in declaration!");
                exit(1);
            }
        } else {
            currentLine = getStringInListByIndex(sourceCode, --currentIndex);
        }
    }
    return NULL;
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
                        exit(1);
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

//Passed JUnitTest!
enum AIOMethodSizeType getSizeTypeOfMethod(StringList *methodCode) {
    if (*methodCode->size == 1) {
        char *trimLine;
        trim(methodCode->strings[0], &trimLine);
        if (isTheShortestInTheSameObject(trimLine) == 0
            || isDefaultOperations(trimLine) == 0
            || isTheShortestInTheOtherObject(trimLine) == 0){
            return THE_SHORTEST;
        } else {
            return SHORT;
        }
    }
    return DEFAULT;
}

//Passed JUnitTest!
AIOMethodDefinition *buildAIOMethodDefinition(char *methodName, StringList *sourceCode, int startIndex) {
    //Create the same method definition:
    AIOMethodDefinition *methodDefinition = calloc(1, sizeof(AIOMethodDefinition));
    if (methodDefinition == NULL) {
        perror("cannot allocate memory for method definition!");
        exit(1);
    }
    //Create aio declaration:
    AIODeclaration *declaration = getDeclarationOfMethod(methodName, sourceCode, startIndex);
    //Create aio annotation list:
    AIOAnnotationList *annotationList = getAnnotationsOfMethod(methodName, sourceCode, startIndex);
    if (isDefaultBehaviour(aioObjectManager) == 0){
        //Create string list of method code:
        StringList *methodCode = getSourceCodeOfMethod(methodName, sourceCode, startIndex);
        //Set method size type:
        enum AIOMethodSizeType sizeType = getSizeTypeOfMethod(methodCode);
        createAIOMethodDefinition(&methodDefinition, methodName, declaration, annotationList, methodCode, sizeType);
        return methodDefinition;
    } else {
        return NULL;
    }
}