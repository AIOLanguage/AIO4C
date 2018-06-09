#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "../../headers/lang/object/objectManager/AIOObjectManager.h"
#include "../../headers/lib/utils/stringUtils/StringUtils.h"

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
  char * a = "0123456789";
  char* b;
  substring(a, 3, 3, &b);
  printf("\nSUBSTRING: -%s-\n", b);


    return 0;
}

//printf("\nAIO OBJECT: -%s-\n", test->name)