#include <malloc.h>
#include <mem.h>
#include "../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../headers/lib/utils/int_utils/int_utils.h"
#include "../../../../headers/lib/utils/double_utils/double_utils.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../headers/lang/aio_function/aio_value/aio_value.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../headers/lang/aio_type/aio_type.h"

aio_value *new_aio_value(const_string undefined_value) {
    aio_value *value = new_object(sizeof(aio_value *));
    if (matches_int(undefined_value)) {
        const int int_value = string_to_int(undefined_value);
        value->int_acc = int_value;
        return value;
    }
    if (matches_double(undefined_value)) {
        const double double_value = string_to_double(undefined_value);
        value->double_acc = double_value;
        return value;
    }
    if (matches_string(undefined_value)) {
        string string_value = remove_prefix_suffix(undefined_value, "\'", "\'");
        value->string_acc = string_value;
        return value;
    }
    if (matches_boolean(undefined_value)) {
        const_boolean boolean_value = string_to_boolean(undefined_value);
        value->boolean_acc = boolean_value;
        return value;
    }
    if (strcmp(undefined_value, VOID) == 0) {
        value->string_acc = (string) undefined_value;
        return value;
    }
    //Ok...
    throw_error("can not define type of aio aio_value");
}

aio_value *new_aio_value_as_int(const int int_acc) {
    aio_value *value = new_object(sizeof(aio_value *));
    value->int_acc = int_acc;
    return value;
}

aio_value *new_aio_value_as_double(const double double_acc) {
    aio_value *value = new_object(sizeof(aio_value *));
    value->double_acc = double_acc;
    return value;
}

aio_value *new_aio_value_as_string(string string_acc) {
    aio_value *value = new_object(sizeof(aio_value *));
    value->string_acc = string_acc;
    return value;
}

aio_value *new_aio_value_as_boolean(const_boolean boolean_acc) {
    aio_value *value = new_object(sizeof(aio_value *));
    value->boolean_acc = boolean_acc;
    return value;
}

void free_aio_value(aio_value *value) {

}

/**
 * List.
 */

aio_value_list *new_aio_value_list() {
    aio_value_list *list = new_object(sizeof(aio_value_list));
    list->capacity = 2;
    list->size = 0;
    list->values = new_object_array(2, sizeof(string));
    return list;
}

static void update_memory_in_aio_value_list(aio_value_list *list) {
    if (list->size == list->capacity) {
        list->capacity = list->capacity * 2;
        list->values = realloc(list->values, list->capacity * sizeof(aio_value *));
    }
}

void add_aio_value_in_list(aio_value_list *string_list, aio_value *value) {
    update_memory_in_aio_value_list(string_list);
    string_list->values[string_list->size] = value;
    string_list->size++;
}

void free_aio_values_in_list(aio_value_list *list) {
    aio_value **values = list->values;
    for (int i = 0; i < list->size; ++i) {
        aio_value *value = values[i];
        if (value != NULL) {
            values[i] = NULL;
            free(value);
        }
    }
}

void free_aio_value_list(aio_value_list *list) {
    free(list->values);
    free(list);
}