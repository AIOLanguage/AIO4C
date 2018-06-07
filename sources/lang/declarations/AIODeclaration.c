#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include "../../../headers/lang/declarations/AIODeclaration.h"

//Passed JUnitTest!
void createAIODeclaration(AIODeclaration **declaration, char* methodName, StringList* args) {
    //Create the same declaration:
    *declaration = (AIODeclaration *) malloc(sizeof(AIODeclaration));
    //Set method name:
    (*declaration)->methodName = methodName;
    //Set args:
    (*declaration)->argList = args;
}