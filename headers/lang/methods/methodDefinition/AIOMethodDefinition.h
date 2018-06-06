#include <malloc.h>
#include "../../declarations/AIODeclaration.h"
#include "../../annotations/AIOAnnotation.h"
#include "AIOMethodSizeType.h"
#include "../../../lib/collections/lists/AIOMutableListOfAnnotations.h"
#include "../../../lib/collections/lists/AIOMutableListOfString.h"

#ifndef AIO_METHOD_DEFINITION_H
#define AIO_METHOD_DEFINITION_H

typedef struct AIOMethodDefinition {
    char *name;
    AIODeclaration *declaration;
    AIOMutableListOfAnnotations *annotations;
    AIOMutableListOfString *sourceCode;
    enum AIOMethodSizeType *methodSizeType;
} AIOMethodDefinition;

void createAIOMethodDefinition(AIOMethodDefinition **methodDefinition, char* name, AIODeclaration* declaration
        , AIOMutableListOfAnnotations* annotations, AIOMutableListOfString* sourceCode, enum AIOMethodSizeType* methodSizeType);

#endif //AIO_METHOD_DEFINITION_H