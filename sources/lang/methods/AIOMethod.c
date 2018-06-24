#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../headers/lang/methods/AIOMethod.h"
#include "../../../headers/lang/object/AIOObject.h"
#include "../../../headers/lib/utils/stringUtils/string_utils.h"

void createAIOMethodContainer(aio_method_container **container) {
    //Create the same aio method container:
    *container = calloc(1, sizeof(aio_method_container));
    if (*container == NULL) {
        perror("can not allocate memory for aio method container!");
    }
    //Create arg map:
    createAIOVariableMap(&(*container)->argMap);
    //Create variable map:
    createAIOVariableMap(&(*container)->variableMap);
}

void setArgs(aio_method_container *methodContainer, aio_declaration *declaration, string_list *inputArgs) {
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
            int_to_str(i, &index);
            strcat(implicitArgumentName, index);
            createAIOVariable(&argument, implicitArgumentName, inputArgs->strings[i], -1, &type);
            putInAIOVariableInMap(methodContainer->argMap, argument);
        }
    }
}

int containsVariableInMap(const char *variableName, const aio_variable_map *variableMap) {
    for (int i = 0; i < *variableMap->size; ++i) {
        if (strcmp(variableName, variableMap->names[i]) == 0) {
            return 0;
        }
    }
    return 1;
}


int containsVariable(char *variableName, aio_method_container *methodContainer) {
    const aio_variable_map *argMap = methodContainer->argMap;
    const aio_variable_map *variableMap = methodContainer->variableMap;
    if (containsVariableInMap(variableName, argMap) == 0) {
        return 0;
    }
    if (containsVariableInMap(variableName, variableMap)) {
        return 0;
    }
    return 1;
}

void setVariable(AIOVariable *variable, aio_method_container *methodContainer) {
    if (canUseName(variable->name) == 0 && containsVariable(variable->name, methodContainer) == 0) {
        putInAIOVariableInMap(methodContainer->variableMap, variable);
    } else {
        perror("there is variable already exists!");
        exit(1);
    }
}

void createAIOMethodAndInvoke(aio_object *object, AIOMethod **method, aio_method_definition *methodDefinition,
                              aio_bundle *bundle) {
    //Create the same aio method:
    *method = calloc(1, sizeof(AIOMethod));
    if (*method == NULL) {
        perror("cannot allocate memory for aio method");
        exit(1);
    }
    //Create method container:
    createAIOMethodContainer(&(*method)->methodContainer);
    //Set args:
    setArgs((*method)->methodContainer, methodDefinition->declaration, bundle->input_values);
    //Reproduce method:
    reproduceMethod(object, methodDefinition, (*method)->methodContainer, bundle);
}