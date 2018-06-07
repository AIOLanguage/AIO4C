#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "../../headers/lang/object/objectManager/AIOObjectManager.h"
#include "../../headers/lang/methods/variable/AIOVariable.h"
#include "../../headers/lib/utils/StringUtils.h"

AIOObjectManager *aioObjectManager;

void init() {
    initAIOObjectManager(&aioObjectManager);
}

int main() {
    init();
//    char * a = "@AS";
//    char * b = malloc(strlen(a));
//    removePrefix(a, "@AS", &b);
    char *path = "../aioPrograms/starter.aio";
    buildAIOObjectAndPutInAIOObjectManager(aioObjectManager, path);
    return 0;
}