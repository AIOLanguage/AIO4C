#include <malloc.h>
#include "../../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../../headers/lang/aio_function/aio_variable/aio_variable_definition/aio_variable_definition.h"
#include "../../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../../headers/lib/utils/string_hook/str_hook.h"
#include "../../../../../headers/lib/utils/string_hook/string_hook_utils/str_hook_utils.h"
#include "../../../../../headers/lib/utils/error_utils/error_utils.h"

#define AIO_VARIABLE_DEFINITION_LIST_TAG "AIO_VARIABLE_DEFINITION_LIST"

aio_variable_definition *new_aio_variable_definition(const_str_hook *name, string type,
                                                     const_boolean is_mutable_by_value) {
    aio_variable_definition definition = {
            .name = name,
            .type = type,
            .is_mutable_by_value = is_mutable_by_value
    };
    aio_variable_definition *variable_definition = new_object(sizeof(aio_variable_definition));
    variable_definition[0] = definition;
    return variable_definition;
}

void free_aio_variable_definition(aio_variable_definition *definition) {
    free_const_str_hook(definition->name);
    free(definition->type);
    free(definition);
}

const_aio_variable_definition *get_variable_definition_in_function_tree(const_str_hook *variable_name,
                                                                        const_aio_function_instruction_holder *holder) {
    const_aio_variable_definition_list *list = holder->variable_definition_list;
    const_aio_variable_definition *definition = get_aio_variable_definition_in_map_by_name(list, variable_name);
    if (definition == NULL) {
        aio_function_instruction_holder *parent_holder = holder->parent;
        if (parent_holder != NULL) {
            return get_variable_definition_in_function_tree(variable_name, parent_holder);
        } else {
            return NULL;
        }
    }
}

aio_variable_definition_list *new_aio_variable_definition_list() {
    aio_variable_definition_list *list = new_object(sizeof(aio_variable_definition_list));
    list->capacity = 2;
    list->size = 0;
    list->definitions = new_object_array(2, sizeof(aio_variable_definition *));
    return list;
}

void update_memory_in_aio_variable_definition_list(aio_variable_definition_list *list) {
    if (list->size + 1 == list->capacity) {
        list->capacity = list->capacity * 2;
        list->definitions = realloc(list->definitions,
                                    list->capacity * sizeof(aio_variable_definition *));
    }
}

void add_aio_variable_definition_in_list(aio_variable_definition_list *list,
                                         const_aio_variable_definition *definition) {
    const_str_hook *name = definition->name;
    const size_t list_size = list->size;
    for (int i = 0; i < list_size; ++i) {
        const_str_hook *current_name = list->definitions[i]->name;
        const_boolean are_equal_strings = are_equal_hooked_str(current_name, name);
        if (are_equal_strings) {
            throw_error_with_tag(AIO_VARIABLE_DEFINITION_LIST_TAG,
                                 "Variable definition with the same name already exists!");
        }
    }
    update_memory_in_aio_variable_definition_list(list);
    list->definitions[list->size] = definition;
    list->size++;
}

const_aio_variable_definition *get_aio_variable_definition_in_map_by_name(const_aio_variable_definition_list *list,
                                                                          const_str_hook *name) {
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

void free_aio_variable_definition_list(aio_variable_definition_list *list) {

}