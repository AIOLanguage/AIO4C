#ifndef AIO_METHOD_DEFINITION_BUILDER_H
#define AIO_METHOD_DEFINITION_BUILDER_H

#include "AIOMethodDefinition.h"

AIOMethodDefinition *buildAIOMethodDefinition(char *methodName, StringList *sourceCode, int startIndex);

int isTheShortestInTheSameObject(const char *operation);

int isTheShortestInTheOtherObject(const char *operation);

#endif //AIO_METHOD_DEFINITION_BUILDER_H