#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include "../../../headers/lang/declarations/AIODeclaration.h"

void createAIODeclaration(AIODeclaration **declaration) {
    *declaration = (AIODeclaration *) calloc(1, sizeof(AIODeclaration));
    AIOMutableListOfString *args;
    createMutableListOfString(&args);
    (*declaration)->argList = args;
}