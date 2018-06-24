#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lang/object/object_manager/aio_object_manager.h"

//Passed JUnitTest!
aio_object_manager *init_aio_object_manager() {
    aio_object_manager *object_manager = calloc(1, sizeof(aio_object_manager));
    if (object_manager == NULL) {
        perror("cannot allocate memory for object_manager");
        exit(1);
    }
    //Set new object map:
    object_manager->objectMap = new_aio_object_map();
    //Set default behaviour:
    object_manager->behaviour = 0;
}

void build_aio_object_and_put_in_object_manager(aio_object_manager *object_manager, char *path) {
    //Create aio object:
    aio_object *aio_object = new_aio_object(new_aio_method_manager(new_aio_method_definition_map()), path);
    //Put new aio object in aio object manager map:
    put_aio_object_in_map(object_manager->objectMap, aio_object);
}

int is_default_behaviour(struct aio_object_manager *object_manager) {
    return object_manager->behaviour;
}