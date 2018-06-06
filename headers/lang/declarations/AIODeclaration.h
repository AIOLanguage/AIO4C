#ifndef AIO_DECLARATION_H
#define AIO_DECLARATION_H

#include "../../lib/collections/lists/AIOMutableListOfString.h"

typedef struct AIODeclaration {
    char* methodName;
    AIOMutableListOfString* argList;
} AIODeclaration;

void createAIODeclaration(AIODeclaration **declaration, char* methodName, AIOMutableListOfString* args);

#endif //AIO_DECLARATION_H