#include <mem.h>
#include <stdio.h>
#include <ctype.h>
#include <process.h>
#include "../../../../headers/lang/methods/methodDefinition/aio_method_definition.h"
#include "../../../../headers/lib/utils/stringUtils/string_utils.h"
#include "../../../../headers/lang/object/objectManager/AIOObjectManager.h"
#include "../../../../headers/lib/utils/operationUtils/OperationUtils.h"

AIOObjectManager* aio_object_manager;

//Passed JUnitTest!
string_list *getSourceCodeOfMethod(char *methodName, string_list *sourceCode, int startIndex) {
    string_list *methodCode;
    new_string_list(&methodCode);
    int currentIndex = startIndex;
    char *trimmedLine;
//    trim(source_code->strings[currentIndex], &trimmedLine);
    if (strcmp(trimmedLine, "") != 0) {
        char *cleanFirstLine = calloc(strlen(trimmedLine) + 1, sizeof(char));
        if (cleanFirstLine == NULL) {
            perror("can not allocate memory for clean first line in during get source code method procedure performs!");
        }
        //remove_prefix(trimmedLine, methodName, &cleanFirstLine);
        if (strcmp(cleanFirstLine, "") != 0) {
            add_in_string_list(methodCode, cleanFirstLine);
        }
        while (++currentIndex < *sourceCode->size) {
            char* currentLine;
//            trim(source_code->strings[currentIndex], &currentLine);
            if (strcmp(currentLine, "") == 0) {
                break;
            } else {
                add_in_string_list(methodCode, currentLine);
            }
        }
    }
    return methodCode;
}

//While empty method:
aio_annotation_list *getAnnotationsOfMethod(char *name, string_list *sourceCode, int startIndex) {
    aio_annotation_list *annotations;
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
string_list *getArgsIfCorrect(char **args) {
    string_list *argList;
    new_string_list(&argList);
    for (int j = 0; j < _msize(args) / 4; ++j) {
        if (is_word(args[j]) == -1) {
            perror("arg in declaration has invalid name!");
            exit(1);
        } else {
            add_in_string_list(argList, args[j]);
        }
    }
    return argList;
}

//Passed JUnitTest!
aio_declaration *getDeclarationOfMethod(char *methodName, string_list *sourceCode, int startIndex) {
    int currentIndex = startIndex - 1;
    char *inputLine = get_string_in_list_by_index(sourceCode, currentIndex);
    char *currentLine;
//    trim(inputLine, &currentLine);
    while (strcmp(currentLine, "") != 0 && currentIndex >= 0) {
        char *declarationPrefix = "~dec:";
        int startsAsDeclaration = starts_with_prefix(currentLine, declarationPrefix);
        if (startsAsDeclaration == 0) {
            //Remove declaration prefix:
            char *bracketLine = malloc(strlen(currentLine));
            if (bracketLine == NULL) {
                perror("cannot allocate memory for bracket line when was creating of declaration!");
                exit(1);
            }
//            remove_prefix(currentLine, declarationPrefix, &bracketLine);
            //<<w+<<:
            if (strlen(bracketLine) > 4 && isCorrectPlacedBrackets(bracketLine) == 0) {
                //Remove brackets:
                char *lp = malloc(strlen(bracketLine));
                if (lp == NULL) {
                    perror("cannot allocate memory for left padding when was creating of declaration!");
                    exit(1);
                }
//                remove_prefix(bracketLine, "<<", &lp);
                char *rp = malloc(strlen(lp));
                if (rp == NULL) {
                    perror("cannot allocate memory for right padding when was creating of declaration!");
                    exit(1);
                }
//                remove_suffix(lp, "<<", &rp);
                //Split naked args;
                char **dirtySplitArgs;
//                split_by_string(rp, ",", &dirtySplitArgs);
                //Trim all args:
                char **args;
//                trim_all(dirtySplitArgs, _msize(dirtySplitArgs) / 4, &args);
                string_list *argList = getArgsIfCorrect(args);
                aio_declaration *aioDeclaration;
                new_aio_declaration(&aioDeclaration, methodName, argList);
                return aioDeclaration;
            } else {
                perror("invalid bracket placement in declaration!");
                exit(1);
            }
        } else {
            currentLine = get_string_in_list_by_index(sourceCode, --currentIndex);
        }
    }
    return NULL;
}

//Passed JUnitTest!
int is_the_shortest_in_the_same_object(const char *operation) {
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
int is_the_shortest_in_the_other_object(const char *operation) {
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
enum aio_method_size_type getSizeTypeOfMethod(string_list *methodCode) {
    if (*methodCode->size == 1) {
        char *trimLine;
//        trim(methodCode->strings[0], &trimLine);
        if (is_the_shortest_in_the_same_object(trimLine) == 0
            || isDefaultOperations(trimLine) == 0
            || is_the_shortest_in_the_other_object(trimLine) == 0){
            return THE_SHORTEST;
        } else {
            return SHORT;
        }
    }
    return DEFAULT;
}

//Passed JUnitTest!
aio_method_definition *build_aio_method_definition(char *method_name, string_list *source_code, int start_index) {
    //Create the same method definition:
    aio_method_definition *methodDefinition = calloc(1, sizeof(aio_method_definition));
    if (methodDefinition == NULL) {
        perror("cannot allocate memory for method definition!");
        exit(1);
    }
    //Create aio declaration:
    aio_declaration *declaration = getDeclarationOfMethod(method_name, source_code, start_index);
    //Create aio annotation list:
    aio_annotation_list *annotationList = getAnnotationsOfMethod(method_name, source_code, start_index);
    if (isDefaultBehaviour(aio_object_manager) == 0){
        //Create string list of method code:
        string_list *methodCode = getSourceCodeOfMethod(method_name, source_code, start_index);
        //Set method size type:
        enum aio_method_size_type sizeType = getSizeTypeOfMethod(methodCode);
        new_aio_method_definition(&methodDefinition, method_name, declaration, annotationList, methodCode, sizeType);
        return methodDefinition;
    } else {
        return NULL;
    }
}