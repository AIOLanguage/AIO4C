#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../headers/lang/methods/AIOMethod.h"

void createAIOMethodContainer(AIOMethodContainer **container) {
    //Create the same aio method container:
    *container = calloc(1, sizeof(AIOMethodContainer));


}

void setArgs(AIODeclaration *declaration, StringList *inputArgs) {

}

void createAIOMethod(AIOMethod **method, AIOMethodDefinition *methodDefinition, AIOBundle *bundle) {
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
    setArgs(methodDefinition->declaration, bundle->inputValues);
}

void invokeAIOMethod(AIOMethod *method) {

}