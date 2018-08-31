#include <malloc.h>
#include "../../../headers/lang/aio_core/aio_core.h"
#include "../../../headers/lang/aio_type/aio_type.h"
#include "../../../headers/lang/aio_context/aio_context.h"
#include "../../../headers/lib/utils/collections/sets/string_set.h"
#include "../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../headers/lib/utils/memory_utils/memory_utils.h"

#define AIO_CORE_TAG

#define AIO_CORE_DEBUG

aio_core *core;

char core_types[NUMBER_OF_CORE_TYPES][4] = {
        {INTEGER},
        {DOUBLE},
        {STRING},
        {BOOLEAN},
        {VOID}
};

void inflate_aio_core()
{
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

const_aio_context *inflate_aio_context_and_put_in_core(const_string context_path)
{
    const_aio_context *context = new_aio_context(context_path);
    add_aio_context_in_list(core->core_context_list, context);
    return context;
}

void deflate_aio_core()
{
    aio_context_list *context_list = core->core_context_list;
    string_set *types = core->aio_type_set;
    //----------------------------------------------------------------------------------------------------------------—
    //찌꺼기 수집기 (Garbage collector):
    free_aio_context_list(context_list);
    free_strings_in_set(types);
    free_string_set(types);
    free(core);
}