#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "../../headers/lang/object/objectManager/AIOObjectManager.h"
#include "../../headers/lang/methods/variable/AIOVariable.h"
#include "../../headers/lib/utils/StringUtils.h"

AIOObjectManager *aioObjectManager;

#define CHUNK 1024

void init(){
    initAIOObjectManager(&aioObjectManager);
}

int main() {
    init();
    char* a = "     ddddaaa                    ";
    char* b = malloc(strlen(a));
    trimEnd(a, &b);
    printf("A: -%s-\n", a);
    printf("B: -%s-\n", b);



    //char* path = "../aioPrograms/starter.aio";
    //buildAIOObjectAndPutInAIOObjectManager(aioObjectManager, path);
    return 0;
}

