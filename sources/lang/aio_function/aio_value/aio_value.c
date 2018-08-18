#include <malloc.h>
#include <mem.h>
#include "../../../../headers/lib/utils/boolean_utils/boolean_utils.h"
#include "../../../../headers/lib/utils/int_utils/int_utils.h"
#include "../../../../headers/lib/utils/double_utils/double_utils.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"
#include "../../../../headers/lang/aio_function/aio_value/aio_value.h"
#include "../../../../headers/lang/aio_types/aio_type.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"

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