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
    char* a = " Hello      AIO!  ";
    char** b;
    splitByChar(a, ' ', &b);
    printf("SIZE:    %d\n", _msize(b) / 4);
    for (int i = 0; i < _msize(b) / 4; ++i) {
        printf("LINE->: -%s-\n", b[i]);
    }



    printf("\n\n\n\n\n\n\n\n\n\nSUCCESSFUL SPLIT!\n");
    char** clean = calloc(_msize(b) / 4, sizeof(char*));
    filter(b, _msize(b) / 4 , &clean, isNotEmpty);
    for (int i = 0; i < _msize(clean) / 4; ++i) {
        printf("CLEAN LINES->: -%s-\n", clean[i]);
    }



//    char *path = "../aioPrograms/starter.aio";
//    buildAIOObjectAndPutInAIOObjectManager(aioObjectManager, path);
    return 0;
}