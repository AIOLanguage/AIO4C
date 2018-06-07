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
    printf("AIO OBJECT: -%s-\n", test->name);
    AIOMethodDefinition *methodDefinition = test->methodManager->methodDefinitionMap->definitions[0];
    for (int i = 0; i < *methodDefinition->declaration->argList->size; ++i) {
        printf("AIO DECLARATION ARGS: -%s-\n", methodDefinition->declaration->argList->strings[i]);
    }
    printf("FIRST ARG NAME: %s\n", methodDefinition->declaration->argList->strings[0]);
}

int main() {
    make();
    return 0;
}


/*
 * char *argLine = "a, b, c";
    char **lines;
    splitByChar(argLine, ' ', &lines);
    for (int i = 0; i < _msize(lines) / 4; ++i) {
        printf("ARGUMENT: -%s-\n", lines[i]);
    }
    char **filtered = calloc(_msize(lines) / 4, sizeof(char *));
    filter(lines, _msize(lines) / 4, &filtered, isNotEmpty);
    char *dst;
    joinToStringWithoutSpaces(filtered, &dst);
    printf("JOINED LINE: -%s-\n", dst);

 */