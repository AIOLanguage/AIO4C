#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "../../headers/lang/object/object_manager/aio_object_manager.h"

aio_object_manager *object_manager;

void init() {
    object_manager = init_aio_object_manager();
}

void make() {
    init();
    char *path = "../aioPrograms/test.aio";
    build_aio_object_and_put_in_object_manager(object_manager, path);
}

int main() {
    return 0;
}

//printf("\n-%s-\n", test)