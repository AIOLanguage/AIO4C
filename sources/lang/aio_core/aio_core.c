#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../headers/lang/aio_core/aio_core.h"
#include "../../../headers/lang/aio_types/aio_type.h"

aio_core *core;

#define AIO_CORE_DEBUG

char core_types[NUMBER_OF_CORE_TYPES][4] = {
        {"Int"},
        {"Dou"},
        {"Str"},
        {"Boo"},
        {VOID}
};

void inflate_aio_core() {
    string_set *type_set = new_string_set();
    //유형를 넣다 (Put core types):
    for (int i = 0; i < NUMBER_OF_CORE_TYPES; ++i) {
        string core_type = core_types[i];
        add_string_in_set(type_set, core_type);
    }
    core = calloc(1, sizeof(aio_core));
    core->core_context_map = new_aio_context_map();
    core->aio_type_set = type_set;
}

void inflate_aio_context_and_put_in_core(const_string path) {
    aio_context *context = new_aio_context(path);
    //put_aio_context_in_map(core->core_context_map, context);
}

boolean contains_aio_type_in_set(const_string string) {
    return contains_string_in_set(core->aio_type_set, string);
}

void destroy_aio_core() {

}