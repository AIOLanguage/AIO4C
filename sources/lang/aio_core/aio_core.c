#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../headers/lang/aio_core/aio_core.h"
#include "../../../headers/lang/aio_types/aio_type.h"

aio_core *core;

char core_types[4][4] = {
        {"Int"},
        {"Dou"},
        {"Str"},
        {VOID}
};

aio_core *init_aio_core() {
    core = calloc(1, sizeof(aio_core));
    core->core_file_map = new_aio_file_map();
    core->aio_type_set = new_string_set();
    //add aio core types:
    for (int i = 0; i < 3; ++i) {
        add_string_in_set(core->aio_type_set, core_types[i]);
    }
}

void build_aio_file_and_put_in_core_file_map(const_string path) {
    //create new aio_file:
    aio_file *aio_object = new_aio_file(path);
    //put new aio_file in aio_file_map:
    put_aio_object_in_map(core->core_file_map, aio_object);
}

boolean contains_aio_type_in_set(const_string string) {
    return contains_string_in_set(core->aio_type_set, string);
}

void delete_aio_core() {

}