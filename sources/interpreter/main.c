#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "../../headers/reservedNames/AIOReservedNamesContainer.h"
#include "../../headers/lang/declarations/AIODeclaration.h"
#include "../../headers/utils/stringUtils/StringUtils.h"



#define INTERPRETER "AIO"

//int main() {
//    printf("%s\n", INTERPRETER);
//
//    struct AIODeclaration dec = {.methodName = "start"};
//    printf("NAME: %s", dec.methodName);
//    return 0;
//}

int main() {
    char* a = "AAAA";
    char* b = "AAA";
    const int c = strcmp(a, b);
    printf("%d", c);

}