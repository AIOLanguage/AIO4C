#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "../../headers/lang/object/objectManager/AIOObjectManager.h"
#include "../../headers/lang/methods/variable/AIOVariable.h"

AIOObjectManager *aioObjectManager;

#define CHUNK 1024

void init(){
    initAIOObjectManager(&aioObjectManager);
}

int main() {
    init();
    char* path = "../aioPrograms/starter.aio";
    buildAIOObjectAndPutInAIOObjectManager(aioObjectManager, path);
    return 0;
}

