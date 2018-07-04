#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lang/object/object_manager/aio_nexus.h"

//Passed JUnitTest!
aio_nexus *init_aio_core() {
    aio_nexus *object_manager = calloc(1, sizeof(aio_nexus));
    if (object_manager == NULL) {
        perror("cannot allocate memory for aio_core");
        exit(1);
    }
    //Set new aio_file map:
    object_manager->objectMap = new_aio_object_map();
    //Set default behaviour:
    object_manager->behaviour = 0;
}

void build_aio_file_and_put_in_core_file_map(struct aio_core *object_manager, char *path) {
    //Create aio aio_file:
    aio_file *aio_object = new_aio_file(new_aio_method_manager(new_aio_method_definition_map()), path);
    //Put new aio aio_file in aio aio_file manager map:
    put_aio_object_in_map(object_manager->objectMap, aio_object);
}

int is_default_behaviour(struct aio_nexus *object_manager) {
    return object_manager->behaviour;
}