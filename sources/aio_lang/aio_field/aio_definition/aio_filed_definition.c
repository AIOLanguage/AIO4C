#include <mem.h>
#include <malloc.h>
#include <aio_lang/aio_field/aio_definition/aio_filed_definition.h>
#include <lib/utils/str_hook/str_hook.h>
#include <lib/utils/boolean_utils/boolean_utils.h>
#include <lib/utils/memory_utils/memory_utils.h>
#include <lib/utils/type_utils/type.utils.h>
#include <aio_tools/aio_function_tools/aio_instructions/aio_function_instruction_holder.h>

#define AIO_VARIABLE_DEFINITION_TAG "AIO_VARIABLE_DEFINITION"

#define AIO_VARIABLE_DEFINITION_DEBUG

#ifdef AIO_VARIABLE_DEFINITION_DEBUG

#include "lib/utils/log_utils/log_utils.h"

#endif

aio_field_definition *new_aio_field_definition(
        str_hook *name,
        str_hook *type,
        boolean is_mutable_by_value
)
{
    aio_field_definition *definition = new_object(sizeof(aio_field_definition));
    definition->name = name;
    definition->type = type;
    definition->is_mutable = is_mutable_by_value;
    return definition;
}

void free_aio_field_definition(aio_field_definition *definition)
{
    free_str_hook(definition->name);
    free(definition->type);
    free(definition);
}

aio_field_definition *request_aio_field_definition(
        const str_hook *variable_name,
        const aio_function_instruction_holder *holder
)
{
    var list = holder->variable_definition_list;
    val definition = get_aio_variable_definition_in_map_by_name(list, variable_name);
    if (!definition) {
        val parent_holder = holder->parent;
        if (parent_holder) {
            return request_aio_field_definition(variable_name, parent_holder);
        } else {
            return NULL;
        }
    } else {
        return definition;
    }
}

aio_field_definition_list *new_aio_field_definition_list()
{
    aio_variable_definition_list *list = new_object(sizeof(aio_variable_definition_list));
    list->capacity = 2;
    list->size = 0;
    list->definitions = new_object_array(2, sizeof(aio_field_definition *));
    return list;
}

static void update_memory_in_aio_variable_definition_list(aio_variable_definition_list *list)
{
    if (list->size + 1 == list->capacity) {
        list->capacity = list->capacity * 2;
        list->definitions = reallocate_object_array(
                list->definitions,
                list->capacity,
                sizeof(aio_field_definition *)
        );
    }
}

void add_aio_field_definition_in_list(
        struct aio_field_definition_list *list,
        aio_field_definition *definition
)
{
    const_str_hook *name = definition->name;
    const size_t list_size = list->size;
    for (int i = 0; i < list_size; ++i) {
        const_str_hook *current_name = list->definitions[i]->name;
        const_boolean are_equal_strings = are_equal_hooked_str(current_name, name);
        if (are_equal_strings) {
            throw_error_with_tag(
                    AIO_VARIABLE_DEFINITION_TAG,
                    "Variable definition with the same name already exists!"
            );
        }
    }
    update_memory_in_aio_variable_definition_list(list);
    list->definitions[list->size] = definition;
    list->size++;
}

aio_field_definition *get_aio_variable_definition_in_map_by_name(
        const aio_field_definition_list *list,
        const str_hook *name
)
{
    const size_t list_size = list->size;
    for (int i = 0; i < list_size; ++i) {
        const_aio_variable_definition *definition = list->definitions[i];
        const_str_hook *current_name = definition->name;
        const_boolean are_equal_strings = are_equal_hooked_str(current_name, name);
        if (are_equal_strings) {
            return definition;
        }
    }
    return NULL;
}

void free_aio_field_definition_list(aio_field_definition_list *list)
{

}

/**
 * Log utils.
 */

void log_info_aio_variable_definition(const_string tag, const_aio_variable_definition *definition)
{
    log_info(tag, "-------------");
    log_info(tag, "DEFINITION: {");
    log_info_str_hook(tag, "<NAME:>", definition->name);
    log_info_str_hook(tag, "<TYPE:>", definition->type);
    log_info_boolean(tag, "<IS_MUTABLE:>", definition->is_mutable);
    log_info(tag, "DEFINITION: }");
    log_info(tag, "-------------");
}