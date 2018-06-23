#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "../../headers/lang/object/objectManager/AIOObjectManager.h"
#include "../../headers/lib/utils/stringUtils/string_utils.h"

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
    StringList *strings;
    createStringList(&strings);
    addInStringList(strings, "    fwbm   ");
    addInStringList(strings, "ddv  ");
    addInStringList(strings, "");
    addInStringList(strings, "     ");
    addInStringList(strings, "f");

    char *a = "   fadvv    ";
    printf("\n-%s-\n", trim(a));
    return 0;
}

//printf("\n-%s-\n", test)