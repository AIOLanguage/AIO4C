#include <stddef.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lang/methods/methodDefinition/AIOMethodDefinition.h"
#include "../../../../headers/lib/lists/AIOMutableListOfAnnotations.h"

void createAIOMethodDefinition(AIOMethodDefinition **methodDefinition, char* name, AIODeclaration* declaration
        , AIOMutableListOfAnnotations* annotations, AIOMutableListOfString* sourceCode
        , enum AIOMethodSizeType* methodSizeType) {
    //Create the same definition:
    *methodDefinition = (AIOMethodDefinition *) calloc(1, sizeof(AIOMethodDefinition));
    //Create definition name:
    (*methodDefinition)->name = name;
    //Create declaration:
    (*methodDefinition)->declaration = declaration;
    //Create annotation list:
    (*methodDefinition)->annotations = annotations;
    //Create source code:
    (*methodDefinition)->sourceCode = sourceCode;
    //Create method size type:
    (*methodDefinition)->methodSizeType = methodSizeType;
}