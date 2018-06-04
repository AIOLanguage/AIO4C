#ifndef AIO_AIO_METHOD_DEFINITION_H
#define AIO_AIO_METHOD_DEFINITION_H

#include "../../declarations/AIODeclaration.h"
#include "../../annotations/AIOAnnotation.h"
#include "../../../lib/AIOMutableListOfString.h"
#include "AIOMethodSizeType.h"

typedef struct AIOMethodDefinition {
    char name[256];
    struct AIODeclaration declaration;
    struct AIOAnnotation annotation;
    struct AIOMutableListOfString listOfString;
    enum AIOMethodSizeType methodSizeType;
} AIOMethodDefinition;

#endif //AIO_AIO_METHOD_DEFINITION_H