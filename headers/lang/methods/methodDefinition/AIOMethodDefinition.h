#include <malloc.h>
#include "../../declarations/AIODeclaration.h"
#include "../../annotations/AIOAnnotation.h"
#include "AIOMethodSizeType.h"
#include "../../../lib/collections/lists/AIOAnnotationList.h"
#include "../../../lib/collections/lists/StringList.h"

#ifndef AIO_METHOD_DEFINITION_H
#define AIO_METHOD_DEFINITION_H

typedef struct AIOMethodDefinition {
    char *name;
    AIODeclaration *declaration;
    AIOAnnotationList *annotations;
    StringList *sourceCode;
    enum AIOMethodSizeType *methodSizeType;
} AIOMethodDefinition;

void createAIOMethodDefinition(AIOMethodDefinition **methodDefinition, char* name, AIODeclaration* declaration
        , AIOAnnotationList* annotations, StringList* sourceCode, enum AIOMethodSizeType* methodSizeType);

#endif //AIO_METHOD_DEFINITION_H