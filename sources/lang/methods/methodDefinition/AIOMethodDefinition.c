#include <stddef.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lang/methods/methodDefinition/AIOMethodDefinition.h"

void createAIOMethodDefinition(AIOMethodDefinition **methodDefinition, char* name, AIODeclaration* declaration
        , AIOMutableListOfAnnotations* annotations, AIOMutableListOfString* sourceCode
        , enum AIOMethodSizeType* methodSizeType) {
    //Create the same definition:
    *methodDefinition = (AIOMethodDefinition *) calloc(1, sizeof(AIOMethodDefinition));
    //Set definition name:
    (*methodDefinition)->name = name;
    //Set declaration:
    (*methodDefinition)->declaration = declaration;
    //Set annotation list:
    (*methodDefinition)->annotations = annotations;
    //Set source code:
    (*methodDefinition)->sourceCode = sourceCode;
    //Set method size type:
    (*methodDefinition)->methodSizeType = methodSizeType;
}