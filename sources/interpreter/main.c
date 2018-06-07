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
    StringList *listOfString;

    createListOfString(&listOfString);
    addInListOfString(listOfString, "");
    addInListOfString(listOfString, "");
    addInListOfString(listOfString, "");
    addInListOfString(listOfString, "Hi");
    addInListOfString(listOfString, "my");
    addInListOfString(listOfString, "favourite");
    addInListOfString(listOfString, "AIO!");

    char **filteredStrings = calloc((size_t) *listOfString->size, sizeof(char *));
    filter(listOfString->strings, (size_t) *listOfString->size, &filteredStrings, isNotEmpty);

    for (int i = 0; i < _msize(filteredStrings) / 4; ++i) {
        printf("--->%s-\n", filteredStrings[i]);
    }

    char *dst;
    joinToString(filteredStrings, " ", &dst);

    printf("JOINED STRING: -%s-\n", dst);

    //char *path = "../aioPrograms/starter.aio";
    //buildAIOObjectAndPutInAIOObjectManager(aioObjectManager, path);
    return 0;
}