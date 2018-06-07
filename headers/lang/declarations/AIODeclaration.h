#ifndef AIO_DECLARATION_H
#define AIO_DECLARATION_H

#include "../../lib/collections/lists/StringList.h"

typedef struct AIODeclaration {
    char* methodName;
    StringList* argList;
} AIODeclaration;

void createAIODeclaration(AIODeclaration **declaration, char* methodName, StringList* args);

#endif //AIO_DECLARATION_H