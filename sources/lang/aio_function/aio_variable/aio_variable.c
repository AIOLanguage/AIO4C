#include <malloc.h>
#include <mem.h>
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lang/aio_function/aio_variable/aio_variable.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"

#define AIO_VARIABLE_DEBUG

#ifdef AIO_VARIABLE_DEBUG

#include "../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

#define AIO_VARIABLE_TAG "AIO_VARIABLE"

aio_variable *new_aio_variable_by_definition(const_aio_variable_definition *variable_definition, aio_value *value)
{
    aio_variable *variable = new_object(sizeof(aio_variable));
    variable->definition = variable_definition;
    variable->value = value;
    variable->init_type = AIO_VARIABLE_NOT_INITIALIZED;
    return variable;
}

aio_variable *get_aio_variable_in_function_control_graph(
        const_str_hook *variable_name,
        const_aio_function_control_graph *control_graph
)
{
    const_aio_variable_list *list = control_graph->variable_list;
#ifdef AIO_VARIABLE_DEBUG
    log_info(AIO_VARIABLE_TAG, "----------------------------------");
    for (int i = 0; i < list->size; ++i) {
        log_info_str_hook(AIO_VARIABLE_TAG, "<NAME:>", list->variables[i]->definition->name);
    }
#endif
    aio_variable *variable = get_aio_variable_in_list_by_name(list, variable_name);
    if (variable == NULL) {
        const_aio_function_control_graph *parent = control_graph->parent;
        if (parent != NULL) {
            return get_aio_variable_in_function_control_graph(variable_name, parent);
        } else {
            return NULL;
        }
    } else {
        const_boolean is_not_reached_variable_in_graph = variable->init_type == AIO_VARIABLE_NOT_INITIALIZED;
        if (is_not_reached_variable_in_graph) {
            return NULL;
        } else {
            return variable;
        }
    }
}

void free_aio_variable(aio_variable *variable)
{

}

/**
 * List
 */

aio_variable_list *new_aio_variable_list()
{
    aio_variable_list *variable_map = new_object(sizeof(aio_variable_list));
    variable_map->capacity = 2;
    variable_map->size = 0;
    variable_map->variables = new_object_array(2, sizeof(aio_variable *));
    return variable_map;
}

void update_memory_in_aio_variable_list(aio_variable_list *variable_map)
{
    if (variable_map->size + 1 == variable_map->capacity) {
        variable_map->capacity = variable_map->capacity * 2;
        variable_map->variables = realloc(variable_map->variables, variable_map->capacity * sizeof(aio_variable *));
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
    for (int i = 0; i < list_size; ++i) {
        const_str_hook *current_name = list->variables[i]->definition->name;
        const_boolean are_equal_strings = are_equal_hooked_str(current_name, name);
        if (are_equal_strings) {
            return list->variables[i];
        }
    }
    return NULL;
}

const struct aio_variable_list *upbuild_variable_map_by_definitions(const_aio_variable_definition_list *list)
{
#ifdef AIO_VARIABLE_DEBUG
    log_info(AIO_VARIABLE_TAG, "Start to build variables...");
    log_info_boolean(AIO_VARIABLE_TAG, "Definition list:", list != NULL);
#endif
    //Extract definition list:
    const size_t definition_list_size = list->size;
    const_aio_variable_definition **definitions = list->definitions;
#ifdef AIO_VARIABLE_DEBUG
    for (int j = 0; j < definition_list_size; ++j) {
        log_info_aio_variable_definition(AIO_VARIABLE_TAG, definitions[j]);
    }
#endif
    //Prepare to building:
    aio_variable_list *variable_list = new_aio_variable_list();
    for (int i = 0; i < definition_list_size; ++i) {
        const_aio_variable_definition *definition = definitions[i];
        aio_variable *new_variable = new_aio_variable_by_definition(definition, NULL);
        add_aio_variable_in_list(variable_list, new_variable);
    }
#ifdef AIO_VARIABLE_DEBUG
    log_info(AIO_VARIABLE_TAG, "Variables are built!");
#endif
    return variable_list;
}