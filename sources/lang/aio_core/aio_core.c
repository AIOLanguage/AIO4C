#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../headers/lang/aio_core/aio_core.h"
#include "../../../headers/lang/aio_types/aio_type.h"

aio_core *core;

char core_types[5][4] = {
        {"Int"},
        {"Dou"},
        {"Str"},
        {"Boo"},
        {VOID}
};

aio_core *init_aio_core() {
    string_set *type_set = new_string_set();
    for (int i = 0; i < sizeof(core_types); ++i) {
        const_string core_type = core_types[i];
        add_string_in_set(type_set, core_type);
    }
    core = calloc(1, sizeof(aio_core));
    core->core_context_map = new_aio_context_map();
    core->aio_type_set = type_set;
}

void build_aio_context_and_put_in_core_contex_map(const_string path) {
    aio_context *aio_context = new_aio_context(path);
    put_aio_context_in_map(core->core_context_map, aio_context);
}

boolean contains_aio_type_in_set(const_string string) {
    return contains_string_in_set(core->aio_type_set, string);
}

void delete_aio_core() {

}