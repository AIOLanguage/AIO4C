#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../headers/lang/aio_core/aio_core.h"
#include "../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../headers/lang/aio_context/aio_context.h"
#include "../../../headers/lib/utils/collections/sets/string_set.h"
#include "../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"
#include "../../../headers/lang/aio_type/aio_type.h"

aio_core *core;

#define AIO_CORE_DEBUG

char core_types[NUMBER_OF_CORE_TYPES][4] = {
        {INTEGER},
        {DOUBLE},
        {STRING},
        {BOOLEAN},
        {VOID}
};

void inflate_aio_core() {
    string_set *type_set = new_string_set();
    //유형를 넣다 (Put core types):
    for (int i = 0; i < NUMBER_OF_CORE_TYPES; ++i) {
        string core_type = core_types[i];
        add_string_in_set(type_set, core_type);
    }
    core = new_object(sizeof(aio_core));
    core->core_context_list = new_aio_context_list();
    core->aio_type_set = type_set;
}

void inflate_aio_context_and_put_in_core(const_string path) {
    const_aio_context *context = new_aio_context(path);
    add_aio_context_in_list(core->core_context_list, context);
}

boolean is_aio_type(const_string string) {
    return contains_string_in_set(core->aio_type_set, string);
}

boolean is_aio_type_hooked(const_str_hook *hook) {
    return contains_string_in_set_by_hook(core->aio_type_set, hook);
}

void free_aio_core() {

}