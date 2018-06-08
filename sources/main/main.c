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


void make() {
    init();
    char *path = "../aioPrograms/test.aio";
    buildAIOObjectAndPutInAIOObjectManager(aioObjectManager, path);
    AIOObject *test = aioObjectManager->objectMap->objects[0];
    printf("\nAIO OBJECT: -%s-\n", test->name);
    AIOMethodDefinition *methodDefinition = test->methodManager->methodDefinitionMap->definitions[0];
    for (int i = 0; i < *methodDefinition->declaration->argList->size; ++i) {
        printf("AIO DECLARATION ARGS: -%s-\n", methodDefinition->declaration->argList->strings[i]);
    }
}

int main() {
    make();
    return 0;
}