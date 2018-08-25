#include <malloc.h>
#include <mem.h>
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lang/aio_function/aio_variable/aio_variable.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"

//#define AIO_VARIABLE_DEBUG

#ifdef AIO_VARIABLE_DEBUG

#include "../../../../headers/lib/utils/log_utils/log_utils.h"

#endif

#define AIO_VARIABLE_TAG "AIO_VARIABLE"

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
#ifdef AIO_VARIABLE_DEBUG
    log_info(AIO_VARIABLE_TAG, "Free value...");
#endif
    free_aio_value(variable->value);
#ifdef AIO_VARIABLE_DEBUG
    log_info(AIO_VARIABLE_TAG, "Free variable...");
#endif
    free(variable);
}

aio_variable *force_get_aio_variable_in_function_control_graph(
        const_str_hook *variable_name,
        const_aio_function_control_graph *control_graph
)
{
#ifdef AIO_VARIABLE_DEBUG
    log_info_str_hook(AIO_VARIABLE_TAG, "Try to get variable:", variable_name);
#endif
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
            log_info(AIO_VARIABLE_TAG, "Parent is not null!");
            return force_get_aio_variable_in_function_control_graph(variable_name, parent);
        } else {
            log_info(AIO_VARIABLE_TAG, "Parent is null!");
            return NULL;
        }
    } else {
#ifdef AIO_VARIABLE_DEBUG
        log_info_aio_variable_definition(AIO_VARIABLE_TAG, variable->definition);
#endif
        return variable;
    }
}

aio_variable *get_aio_variable_in_function_control_graph(
        const_str_hook *variable_name,
        const_aio_function_control_graph *control_graph
)
{
#ifdef AIO_VARIABLE_DEBUG
    log_info(AIO_VARIABLE_TAG, "Start to find variable in graph...");
#endif
    aio_variable *variable = force_get_aio_variable_in_function_control_graph(variable_name, control_graph);
    if (variable != NULL) {
        const_boolean is_not_reached_variable_in_graph = variable->init_type == AIO_VARIABLE_NOT_INITIALIZED;
        if (is_not_reached_variable_in_graph) {
            return NULL;
        } else {
            return variable;
        }
    } else {
        return NULL;
    }
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

void free_aio_variable_list(const_aio_variable_list *list)
{
    const size_t list_size = list->size;
    aio_variable_array variable_array = list->variables;
    for (int i = 0; i < list_size; ++i) {
        aio_variable *variable = variable_array[i];
        if (variable != NULL) {
#ifdef AIO_VARIABLE_DEBUG
            log_info(AIO_VARIABLE_TAG, "Free");
            log_info_aio_variable_definition(AIO_VARIABLE_TAG, variable->definition);
#endif
            variable_array[i] = NULL;
            free_aio_variable(variable);
        }
    }
#ifdef AIO_VARIABLE_DEBUG
    log_info(AIO_VARIABLE_TAG, "Variables are cleared!");
#endif
    free(variable_array);
    free((void *) list);
}

const struct aio_variable_list *upbuild_variable_map_by_definitions(const_aio_variable_definition_list *list)
{
#ifdef AIO_VARIABLE_DEBUG
    log_info(AIO_VARIABLE_TAG, "Start to build variables...");
    log_info_boolean(AIO_VARIABLE_TAG, "Definition list:", list != NULL);
#endif
    //Extract definition list:
    const size_t definition_list_size = list->size;
    aio_variable_definition **definitions = list->definitions;
#ifdef AIO_VARIABLE_DEBUG
    for (int j = 0; j < definition_list_size; ++j) {
        log_info_aio_variable_definition(AIO_VARIABLE_TAG, definitions[j]);
        log_info(AIO_VARIABLE_TAG, "...");
    }
#endif
    //Prepare to building:
#ifdef AIO_VARIABLE_DEBUG
    log_info(AIO_VARIABLE_TAG, "Create variable list...");
#endif
    aio_variable_list *variable_list = new_aio_variable_list();
    for (int i = 0; i < definition_list_size; ++i) {
        aio_variable_definition *definition = definitions[i];
#ifdef AIO_VARIABLE_DEBUG
        log_info(AIO_VARIABLE_TAG, "Create variable...");
#endif
        aio_variable *new_variable = new_aio_variable_by_definition(definition, NULL);
#ifdef AIO_VARIABLE_DEBUG
        log_info(AIO_VARIABLE_TAG, "Add variable to list...");
#endif
        add_aio_variable_in_list(variable_list, new_variable);
    }
#ifdef AIO_VARIABLE_DEBUG
    log_info(AIO_VARIABLE_TAG, "Variables are built!");
#endif
    return variable_list;
}