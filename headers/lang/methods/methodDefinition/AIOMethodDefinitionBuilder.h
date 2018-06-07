#ifndef AIO_METHOD_DEFINITION_BUILDER_H
#define AIO_METHOD_DEFINITION_BUILDER_H

#include "AIOMethodDefinition.h"

AIOMethodDefinition *buildAIOMethodDefinition(char *methodName, AIOMutableListOfString *sourceCode, int startIndex);

#endif //AIO_METHOD_DEFINITION_BUILDER_H