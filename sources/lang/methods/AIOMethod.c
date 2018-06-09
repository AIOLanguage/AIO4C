#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../headers/lang/methods/AIOMethod.h"
#include "../../../headers/lang/object/AIOObject.h"
#include "../../../headers/lib/utils/stringUtils/StringUtils.h"

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
            createAIOVariable(&argument, declaration->argList->strings[i], inputArgs->strings[i], -1,);
            putAIOVariableInMap(methodContainer->argMap, argument);
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
            intToString(i, &index);
            strcat(implicitArgumentName, index);
            createAIOVariable(&argument, implicitArgumentName, inputArgs->strings[i], -1, &type);
            putAIOVariableInMap(methodContainer->argMap, argument);
        }
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
    //Create method methodReproducer:
    createAIOMethodReproducer(&(*method)->methodReproducer, methodDefinition, (*method)->methodContainer, bundle);
    //Set args:
    setArgs((*method)->methodContainer, methodDefinition->declaration, bundle->inputValues);
    //Reproduce method:
    reproduceMethod(object, methodDefinition, (*method)->methodContainer, bundle);
}