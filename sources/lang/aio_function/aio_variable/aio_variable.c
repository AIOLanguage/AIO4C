#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../../headers/lang/aio_types/aio_type.h"
#include "../../../../headers/lib/utils/double_utils/double_utils.h"
#include "../../../../headers/lib/utils/int_utils/int_utils.h"
#include "../../../../headers/lang/aio_function/aio_variable/aio_variable.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../headers/lib/utils/string_hook/str_hook.h"
#include "../../../../headers/lib/utils/string_hook/string_hook_utils/str_hook_utils.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"

#define AIO_VARIABLE_LIST_TAG "AIO_VARIABLE_LIST"

aio_variable *new_aio_variable_by_definition(const_aio_variable_definition *variable_definition, aio_value *value) {
    aio_variable *variable = new_object(sizeof(aio_variable));
    variable->variable_definition = variable_definition;
    variable->value = value;
    return variable;
}

void free_aio_variable(aio_variable *variable) {

}

/**
 * List
 */

aio_variable_list *new_aio_variable_list() {
    aio_variable_list *variable_map = new_object(sizeof(aio_variable_list));
    variable_map->capacity = 2;
    variable_map->size = 0;
    variable_map->variables = new_object_array(2, sizeof(aio_variable *));
    return variable_map;
}

void update_memory_in_aio_variable_list(aio_variable_list *variable_map) {
    if (variable_map->size + 1 == variable_map->capacity) {
        variable_map->capacity = variable_map->capacity * 2;
        variable_map->variables = realloc(variable_map->variables, variable_map->capacity * sizeof(aio_variable *));
    }
}

void add_aio_variable_in_list(aio_variable_list *list, aio_variable *variable) {
    const_str_hook *name = variable->variable_definition->name;
    for (int i = 0; i < list->size; ++i) {
        const_str_hook *current_name = list->variables[i]->variable_definition->name;
        const_boolean are_equal_strings = are_equal_hooked_str(current_name, name);
        if (are_equal_strings) {
            throw_error_with_tag(AIO_VARIABLE_LIST_TAG, "Variable already exists!");
        }
    }
    update_memory_in_aio_variable_list(list);
    list->variables[list->size] = variable;
    list->size++;
}

aio_variable *get_aio_variable_in_list_by_name(const_aio_variable_list *list, const_str_hook *name) {
    const size_t list_size = list->size;
    for (int i = 0; i < list_size; ++i) {
        const_str_hook *current_name = list->variables[i]->variable_definition->name;
        const_boolean are_equal_strings = are_equal_hooked_str(current_name, name);
        if (are_equal_strings) {
            return list->variables[i];
        }
    }
    return NULL;
}