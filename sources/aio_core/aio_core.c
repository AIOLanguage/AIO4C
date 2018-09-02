#include <malloc.h>
#include <aio_core/aio_core.h>
#include <aio_lang/aio_type/aio_type.h>
#include <lib/utils/str_hook/str_hook.h>
#include <lib/utils/str_hook/str_hook_utils/str_hook_utils.h>
#include <aio_tools/aio_common_tools/aio_utils/aio_bundle/aio_bundle.h>
#include <lib/utils/memory_utils/memory_utils.h>
#include <aio_core/aio_context/aio_context.h>
#include <aio_lang/aio_class/aio_class.h>
#include <aio_lang/aio_function/aio_function_definition/aio_function_definition.h>
#include <aio_lang/aio_field/aio_definition/aio_filed_definition.h>
#include <aio_tools/aio_common_tools/aio_utils/aio_value/aio_value.h>
#include <lib/utils/type_utils/type.utils.h>

#define AIO_CORE_TAG

#define AIO_CORE_DEBUG

aio_core *core;

static char core_types[NUMBER_OF_CORE_TYPES][4] = {
        {INTEGER},
        {DOUBLE},
        {STRING},
        {BOOLEAN},
        {VOID}
};

static str_hook_list *create_root_type_set()
{
    var types = new_str_hook_list();
    //유형를 넣다 (Put core types):
    for (int i = 0; i < NUMBER_OF_CORE_TYPES; ++i) {
        var core_type = new_str_hook_by_string(core_types[i]);
        add_str_hook_in_list(types, core_type);
    }
    return types;
}

aio_value_list *inflate_aio_core(aio_bundle *input_bundle)
{
    //Init:
    core = new_object(sizeof(aio_core));
    core->aio_type_set = create_root_type_set();
    core->context_list = new_aio_context_list();
    //Meta data:
    core->class_list = new_aio_class_list();
    core->global_function_definition_list = new_aio_function_definition_list();
    core->global_field_definition_list = new_aio_field_definition_list();
    //Open context:
    aio_value_list *result_list = inflate_aio_context(input_bundle);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    //Free type set:
    free_str_hooks_in_list(core->aio_type_set);
    free_str_hook_list(core->aio_type_set);
    //Free class list:
    free_aio_class_list(core->class_list);
    //Free global function definition list:
    free_aio_function_definition_list(core->global_function_definition_list);
    //Free global field definition list:
    free_aio_field_definition_list(core->global_field_definition_list);
    //Free core:
    free(core);
    return result_list;
}