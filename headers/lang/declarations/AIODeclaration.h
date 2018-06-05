#include "../../lib/lists/AIOMutableListOfString.h"

#ifndef AIO_DECLARATION_H
#define AIO_DECLARATION_H

typedef struct AIODeclaration {
    char* methodName;
    AIOMutableListOfString* argList;
} AIODeclaration;

void createAIODeclaration(AIODeclaration **declaration, char* methodName, AIOMutableListOfString* args);

#endif //AIO_DECLARATION_H