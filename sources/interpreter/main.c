#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../headers/reservedNames/AIOReservedNamesContainer.h"
#include "../../headers/lang/declarations/AIODeclaration.h"
#include "../../headers/lib/AIOMutableListOfString.h"

//int main() {
//    printf("%s\n", INTERPRETER);
//
//    struct AIODeclaration dec = {.methodName = "start"};
//    printf("NAME: %s", dec.methodName);
//    return 0;
//}

int main() {
    struct AIOMutableListOfString listOfString = mutableListOfString();
    char a [] = "33333";
    addInMutableListOfString(&listOfString, a);
    printf("%s\n", listOfString.strings[0]);
    printf("%d\n", listOfString.size);

    char* z = getStringInMutableListByIndex(&listOfString, 0);
    printf("%s\n", z);
    return 0;
}