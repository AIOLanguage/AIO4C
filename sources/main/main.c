#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "../../headers/lang/object/objectManager/AIOObjectManager.h"

AIOObjectManager *aioObjectManager;

void init() {
    initAIOObjectManager(&aioObjectManager);
}

void make() {
    init();
    char *path = "../aioPrograms/test.aio";
    buildAIOObjectAndPutInAIOObjectManager(aioObjectManager, path);
}

int main() {
    make();
    return 0;
}

//printf("\nAIO OBJECT: -%s-\n", test->name)