#include <malloc.h>
#include <mem.h>
#include <lang/aio_function/aio_variable/aio_variable.h>
#include <lang/aio_function/aio_variable/aio_definition/aio_variable_definition.h>
#include <lang/aio_function/aio_value/aio_value.h>
#include <lib/utils/memory_utils/memory_utils.h>
#include <lib/utils/str_hook/str_hook.h>
#include <lib/utils/boolean_utils/boolean_utils.h>
#include <lib/utils/str_hook/str_hook_utils/str_hook_utils.h>
#include <lib/utils/error_utils/error_utils.h>

#define AIO_VARIABLE_DEBUG

#ifdef AIO_VARIABLE_DEBUG

#endif

#define AIO_VARIABLE_TAG "AIO_VARIABLE"

/**
 * Business logic
 */

aio_variable *new_aio_variable_by_definition(aio_variable_definition *variable_definition, aio_value *value)
{
    aio_variable *variable = new_object(sizeof(aio_variable));
    variable->definition = variable_definition;
    variable->value = value;
    variable->init_type = AIO_VARIABLE_NOT_INITIALIZED;
    return variable;
}

void free_aio_variable(aio_variable *variable)
{
    free_aio_value(variable->value);
    free(variable);
}

/**
 * List
 */

aio_variable_list *new_aio_variable_list()
{
    aio_variable_list *list = new_object(sizeof(aio_variable_list));
    list->capacity = 2;
    list->size = 0;
    list->variables = new_object_array(2, sizeof(aio_variable *));
    return list;
}

static void update_memory_in_aio_variable_list(aio_variable_list *variable_map)
{
    if (variable_map->size + 1 == variable_map->capacity) {
        variable_map->capacity = variable_map->capacity * 2;
        variable_map->variables = reallocate_object_array(
                variable_map->variables,
                variable_map->capacity,
                sizeof(aio_variable *)
        );
    }
}

void add_aio_variable_in_list(aio_variable_list *list, aio_variable *variable)
{
    const_str_hook *name = variable->definition->name;
    for (int i = 0; i < list->size; ++i) {
        const_str_hook *current_name = list->variables[i]->definition->name;
        const_boolean are_equal_strings = are_equal_hooked_str(current_name, name);
        if (are_equal_strings) {
            throw_error_with_tag(AIO_VARIABLE_TAG, "Variable already exists!");
        }
    }
    update_memory_in_aio_variable_list(list);
    list->variables[list->size] = variable;
    list->size++;
}

aio_variable *get_aio_variable_in_list_by_name(const_aio_variable_list *list, const_str_hook *name)
{
    const size_t list_size = list->size;
    aio_variable_array variables = list->variables;
    for (int i = 0; i < list_size; ++i) {
        const_str_hook *current_name = variables[i]->definition->name;
        const_boolean are_equal_strings = are_equal_hooked_str(current_name, name);
        if (are_equal_strings) {
            return list->variables[i];
        }
    }
    return NULL;
}

void free_aio_variable_list(const_aio_variable_list *list)
{
    const size_t list_size = list->size;
    aio_variable_array variable_array = list->variables;
    for (int i = 0; i < list_size; ++i) {
        aio_variable *variable = variable_array[i];
        if (variable) {
            variable_array[i] = NULL;
            free_aio_variable(variable);
        }
    }
    free(variable_array);
    free((void *) list);
}