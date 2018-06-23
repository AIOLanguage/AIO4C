#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../headers/lang/methods/AIOMethod.h"
#include "../../../headers/lang/object/AIOObject.h"
#include "../../../headers/lib/utils/stringUtils/string_utils.h"

void createAIOMethodContainer(AIOMethodContainer **container) {
    //Create the same aio method container:
    *container = calloc(1, sizeof(AIOMethodContainer));
    if (*container == NULL) {
        perror("can not allocate memory for aio method container!");
    }
    //Create arg map:
    createAIOVariableMap(&(*container)->argMap);
    //Create variable map:
    createAIOVariableMap(&(*container)->variableMap);
}

void setArgs(AIOMethodContainer *methodContainer, AIODeclaration *declaration, StringList *inputArgs) {
    //I checked args size with declaration before creating of method!
    if (declaration != NULL) {
        for (int i = 0; i < *declaration->argList->size; ++i) {
            //Input args is immutable:
            //Compare input value type:
            AIOVariable *argument;
            enum AIOType type;
            setType(inputArgs->strings[i], &type);
            createAIOVariable(&argument, declaration->argList->strings[i], inputArgs->strings[i], -1, &type);
            putInAIOVariableInMap(methodContainer->argMap, argument);
        }
    } else {
        for (int i = 0; i < *inputArgs->size; i++) {
            //Input args is immutable:
            //Compare input value type:
            AIOVariable *argument;
            enum AIOType type;
            setType(inputArgs->strings[i], &type);
            char *implicitArgumentName = "<<";
            char *index;
            intToStr(i, &index);
            strcat(implicitArgumentName, index);
            createAIOVariable(&argument, implicitArgumentName, inputArgs->strings[i], -1, &type);
            putInAIOVariableInMap(methodContainer->argMap, argument);
        }
    }
}

int containsVariableInMap(const char *variableName, const AIOVariableMap *variableMap) {
    for (int i = 0; i < *variableMap->size; ++i) {
        if (strcmp(variableName, variableMap->names[i]) == 0) {
            return 0;
        }
    }
    return 1;
}


int containsVariable(char *variableName, AIOMethodContainer *methodContainer) {
    const AIOVariableMap *argMap = methodContainer->argMap;
    const AIOVariableMap *variableMap = methodContainer->variableMap;
    if (containsVariableInMap(variableName, argMap) == 0) {
        return 0;
    }
    if (containsVariableInMap(variableName, variableMap)) {
        return 0;
    }
    return 1;
}

void setVariable(AIOVariable *variable, AIOMethodContainer *methodContainer) {
    if (canUseName(variable->name) == 0 && containsVariable(variable->name, methodContainer) == 0) {
        putInAIOVariableInMap(methodContainer->variableMap, variable);
    } else {
        perror("there is variable already exists!");
        exit(1);
    }
}

void createAIOMethodAndInvoke(AIOObject *object, AIOMethod **method, AIOMethodDefinition *methodDefinition,
                              AIOBundle *bundle) {
    //Create the same aio method:
    *method = calloc(1, sizeof(AIOMethod));
    if (*method == NULL) {
        perror("cannot allocate memory for aio method");
        exit(1);
    }
    //Create method container:
    createAIOMethodContainer(&(*method)->methodContainer);
    //Set args:
    setArgs((*method)->methodContainer, methodDefinition->declaration, bundle->inputValues);
    //Reproduce method:
    reproduceMethod(object, methodDefinition, (*method)->methodContainer, bundle);
}