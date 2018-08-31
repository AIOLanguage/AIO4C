#include <malloc.h>
#include <lang/aio_core/aio_core.h>
#include <lang/aio_type/aio_type.h>
#include <lib/utils/collections/sets/string_set.h>
#include <lib/utils/string_utils/string_utils.h>
#include <lib/utils/memory_utils/memory_utils.h>
#include <lang/aio_class/aio_class.h>
#include <lang/aio_function/aio_function_definition/aio_function_definition.h>
#include <lang/aio_field/definition/aio_field_definition.h>

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

static string_set *create_root_type_set()
{
    string_set *type_set = new_string_set();
    //유형를 넣다 (Put core types):
    for (int i = 0; i < NUMBER_OF_CORE_TYPES; ++i) {
        string core_type = new_string(core_types[i]);
        add_string_in_set(type_set, core_type);
    }
    return type_set;
}

void inflate_aio_core()
{
    //Init
    core = new_object(sizeof(aio_core));
    core->aio_type_set = create_root_type_set();
    core->class_list = new_aio_class_list();
    core->global_function_definition_list = new_aio_function_definition_list();
    core->global_field_definition_list = new_aio_field_definition_list();
    inflate_aio_context(file_path);

}

void deflate_aio_core()
{
    string_set *types = core->aio_type_set;
    aio_class_list *class_list = core->class_list;
    aio_function_definition_list *global_function_definition_list = core->global_function_definition_list;
    aio_field_definition_list *global_field_definition_list = core->global_field_definition_list;
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기 (Garbage collector):
    //Free type set:
    free_strings_in_set(types);
    free_string_set(types);
    //Free class list:
    free_aio_class_list(class_list);
    //Free global function definition list:
    free_aio_function_definition_list(global_function_definition_list);
    //Free global field definition list:
    free_aio_field_definition_list(global_field_definition_list);
    //Free core:
    free(core);
}