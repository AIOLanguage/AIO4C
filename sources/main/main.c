#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "../../headers/lang/object/object_manager/aio_nexus.h"

aio_nexus *core;

void init() {
    core = init_aio_object_manager();
}

void make() {
    init();
    char *path = "../aioPrograms/test.aio";
    build_aio_object_and_put_in_object_manager(core, path);
}

int main() {
    return 0;
}

//printf("\n-%s-\n", test)