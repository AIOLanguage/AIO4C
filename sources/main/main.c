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
    addInStringList(strings, "s");
    addInStringList(strings, "");
    printf("\nSIZE:-%d-\n", *strings->size);
    char **clean_strings = filter(strings->strings, *strings->size, is_not_empty_string);

    for (int i = 0; i < _msize(clean_strings) / 4; ++i) {
        strings->strings[i] = trim(clean_strings[i]);
        printf("\n-%s-\n", strings->strings[i]);
    }
    printf("\n-%s-\n", join_to_string(strings->strings, "|", *strings->size));

    char* a = "sffsfs";
    char* b = substring("ssw||||", 2, 4);
    printf("\nB   -%s-\n", b);
    printf("\nA   -%s-\n", a);


    concat_char_to_string(b, '!');;
    printf("\nCONCAT:-%s-\n", b);
    return 0;
}

//printf("\n-%s-\n", test)