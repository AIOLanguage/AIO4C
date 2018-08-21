#include <malloc.h>
#include <mem.h>
#include "../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../headers/lib/utils/int_utils/int_utils.h"
#include "../../../../headers/lib/utils/double_utils/double_utils.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../headers/lang/aio_function/aio_value/aio_value.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../../headers/lang/aio_type/aio_type.h"
#include "../../../../headers/lib/utils/str_hook/str_hook_utils/str_hook_utils.h"

#define AIO_VALUE_TAG "AIO_VALUE"

aio_value *new_aio_value(string undefined_value) {
    if (matches_int(undefined_value)) {
        const int int_value = string_to_int(undefined_value);
        free(undefined_value);
        return new_aio_int_value(int_value);
    }
    if (matches_double(undefined_value)) {
        const double double_value = string_to_double(undefined_value);
        free(undefined_value);
        return new_aio_double_value(double_value);
    }
    if (matches_string(undefined_value)) {
        string string_value = remove_prefix_suffix(undefined_value, "\'", "\'");
        free(undefined_value);
        return new_aio_string_value(string_value);
    }
    if (matches_boolean(undefined_value)) {
        const_boolean boolean_value = string_to_boolean(undefined_value);
        free(undefined_value);
        return new_aio_boolean_value(boolean_value);
    } else {
        throw_error_with_tag(AIO_VALUE_TAG, "Classes are not yet developed in AIO");
    }
}

aio_value *new_aio_int_value(const int int_acc) {
    aio_value *value = new_object(sizeof(aio_value *));
    value->get.int_acc = int_acc;
    value->type = new_str_hook_by_string(INTEGER);
    return value;
}

aio_value *new_aio_double_value(const double double_acc) {
    aio_value *value = new_object(sizeof(aio_value *));
    value->get.double_acc = double_acc;
    value->type = new_str_hook_by_string(DOUBLE);
    return value;
}

aio_value *new_aio_string_value(const_string string_acc) {
    aio_value *value = new_object(sizeof(aio_value *));
    value->get.string_acc = new_string(string_acc);
    value->type = new_str_hook_by_string(STRING);
    return value;
}

aio_value *new_aio_boolean_value(const_boolean boolean_acc) {
    aio_value *value = new_object(sizeof(aio_value *));
    value->get.boolean_acc = boolean_acc;
    value->type = new_str_hook_by_string(BOOLEAN);
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