#include <stddef.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lang/aio_function/aio_function_definition/aio_function_definition.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../headers/lib/utils/string_hook/string_hook_utils/str_hook_utils.h"

#define AIO_FUNCTION_DEFINITION_TAG "AIO_FUNCTION_DEFINITION"

/**
 * Definition.
 */

const_aio_function_definition *new_aio_function_definition(const_aio_annotation_list *annotations,
                                                           const_str_hook_list *output_type_list,
                                                           const_str_hook *name, const int number_of_args,
                                                           const_aio_function_instruction_holder *instruction_holder) {
    aio_function_definition definition = {
            .annotation_list = annotations,
            .output_type_list = output_type_list,
            .name = name,
            .number_of_args = number_of_args,
            .root_holder = instruction_holder
    };
    aio_function_definition *function_definition = new_object(sizeof(aio_function_definition));
    function_definition[0] = definition;
    return function_definition;
}

void free_aio_function_definition(const_aio_function_definition *method_definition) {

}

/**
 * List.
 */

aio_function_definition_list *new_aio_function_definition_list() {
    aio_function_definition_list *list = new_object(sizeof(aio_function_definition_list));
    list->capacity = 2;
    list->size = 0;
    list->definitions = new_object_array(2, sizeof(aio_function_definition *));
    return list;
}

void update_memory_in_function_definition_list(aio_function_definition_list *list) {
    if (list->size + 1 == list->capacity) {
        list->capacity = list->capacity * 2;
        list->definitions = realloc(list->definitions, list->capacity * sizeof(aio_function_definition));
    }
}

void add_aio_function_definition_in_list(struct aio_function_definition_list *list,
                                         const_aio_function_definition *definition) {
    const_str_hook *definition_name = definition->name;
    for (int i = 0; i < list->size; ++i) {
        const_str_hook *current_name = list->definitions[i]->name;
        const_boolean are_equal_strings = are_equal_hooked_str(current_name, definition_name);
        if (are_equal_strings) {
            throw_error_with_tag(AIO_FUNCTION_DEFINITION_TAG, "definition with the same name already exists!");
        }
    }
    //Check from update:
    update_memory_in_function_definition_list(list);
    list->definitions[list->size] = definition;
    list->size++;
}

const_aio_function_definition *get_aio_method_definition_in_list_by_name(const_aio_function_definition_list *list,
                                                                         const_str_hook *name) {
    for (int i = 0; i < list->size; ++i) {
        const_str_hook *current_name = list->definitions[i]->name;
        const_boolean are_equal_strings = are_equal_hooked_str(current_name, name);
        if (are_equal_strings) {
            return list->definitions[i];
        }
    }
    throw_error_with_tag(AIO_FUNCTION_DEFINITION_TAG, "Can not get aio function definition in list!!!");
}