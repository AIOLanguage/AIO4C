#include <aio_lang/aio_types/aio_type.h>
#include <aio_utils/aio_value/aio_value.h>
#include <lib4aio_cpp_headers/utils/string_utils/common.h>

bool are_equal_aio_values(aio_value *value_1, aio_value *value_2)
{
    if (!value_1) {
        return !value_2;
    } else {
        if (!value_2) {
            return false;
        }
    }
    auto type_1 = value_1->type;
    if (type_1->equals_string(INTEGER)) {
        auto new_value_2 = cast_to_int(value_2);
        auto are_equal = value_1->get.int_acc == new_value_2->get.int_acc;
        return are_equal;
    }
    if (type_1->equals_string(DOUBLE)) {
        auto new_value_2 = cast_to_double(value_2);
        auto are_equal = value_1->get.double_acc == new_value_2->get.double_acc;
        return are_equal;
    }
    if (type_1->equals_string(STRING)) {
        auto new_value_2 = cast_to_string(value_2);
        auto are_equal = are_equal_strings(value_1->get.string_acc, new_value_2->get.string_acc);
        return are_equal;
    }
    if (type_1->equals_string(BOOLEAN)) {
        auto new_value_2 = cast_to_boolean(value_2);
        auto are_equal = value_1->get.boolean_acc == new_value_2->get.boolean_acc;
        return are_equal;
    } else {
        //Compare references:
        auto are_equal = value_1->get.reference == value_2->get.reference;
        return are_equal;
    }
}

boolean are_not_equal_aio_values(aio_value *value_1, aio_value *value_2)
{
    if (!value_1) {
        if (value_2) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else {
        if (!value_2) {
            return TRUE;
        }
    }
    const_str_hook *type_1 = value_1->type;
    if (is_hook_equals_str(type_1, INTEGER)) {
        aio_value *new_value_2 = cast_to_int(value_2);
        return value_1->get.int_acc != new_value_2->get.int_acc;
    }
    if (is_hook_equals_str(type_1, DOUBLE)) {
        aio_value *new_value_2 = cast_to_double(value_2);
        return value_1->get.double_acc != new_value_2->get.double_acc;
    }
    if (is_hook_equals_str(type_1, STRING)) {
        aio_value *new_value_2 = cast_to_string(value_2);
        return !are_equal_strings(value_1->get.string_acc, new_value_2->get.string_acc);
    }
    if (is_hook_equals_str(type_1, BOOLEAN)) {
        aio_value *new_value_2 = cast_to_boolean(value_2);
        return value_1->get.boolean_acc != new_value_2->get.boolean_acc;
    } else {
        return value_1->get.reference != value_2->get.reference;
    }
}

boolean is_more_aio_value_then_other(aio_value *value_1, aio_value *value_2)
{
    if (!value_1) {
        throw_error_with_tag(AIO_VALUE_TAG, "Left value is null!");
    }
    if (!value_2) {
        throw_error_with_tag(AIO_VALUE_TAG, "Right value is null!");
    }
    const_str_hook *type_1 = value_1->type;
    if (is_hook_equals_str(type_1, INTEGER)) {
        aio_value *new_value_2 = cast_to_int(value_2);
        return value_1->get.int_acc > new_value_2->get.int_acc;
    }
    if (is_hook_equals_str(type_1, DOUBLE)) {
        aio_value *new_value_2 = cast_to_double(value_2);
        return value_1->get.double_acc > new_value_2->get.double_acc;
    }
    if (is_hook_equals_str(type_1, STRING)) {
        aio_value *new_value_2 = cast_to_string(value_2);
        return strcmp(value_1->get.string_acc, new_value_2->get.string_acc) > 0;
    } else {
        throw_error_with_hook(AIO_VALUE_TAG, "Can not compare values by type:", type_1);
    }
}

boolean is_more_or_equals_aio_value_then_other(aio_value *value_1, aio_value *value_2)
{
    if (!value_1) {
        if (!value_2) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else {
        if (!value_2) {
            return FALSE;
        }
    }
    const_str_hook *type_1 = value_1->type;
    if (is_hook_equals_str(type_1, INTEGER)) {
        aio_value *new_value_2 = cast_to_int(value_2);
        return value_1->get.int_acc >= new_value_2->get.int_acc;
    }
    if (is_hook_equals_str(type_1, DOUBLE)) {
        aio_value *new_value_2 = cast_to_double(value_2);
        return value_1->get.double_acc >= new_value_2->get.double_acc;
    }
    if (is_hook_equals_str(type_1, STRING)) {
        aio_value *new_value_2 = cast_to_string(value_2);
        return strcmp(value_1->get.string_acc, new_value_2->get.string_acc) >= 0;
    } else {
        throw_error_with_hook(AIO_VALUE_TAG, "Can not compare values by type:", type_1);
    }
}

boolean is_less_aio_value_then_other(aio_value *value_1, aio_value *value_2)
{
    if (!value_1) {
        throw_error_with_tag(AIO_VALUE_TAG, "Left value is null!");
    }
    if (!value_2) {
        throw_error_with_tag(AIO_VALUE_TAG, "Right value is null!");
    }
    const_str_hook *type_1 = value_1->type;
    if (is_hook_equals_str(type_1, INTEGER)) {
        aio_value *new_value_2 = cast_to_int(value_2);
        return value_1->get.int_acc < new_value_2->get.int_acc;
    }
    if (is_hook_equals_str(type_1, DOUBLE)) {
        aio_value *new_value_2 = cast_to_double(value_2);
        return value_1->get.double_acc < new_value_2->get.double_acc;
    }
    if (is_hook_equals_str(type_1, STRING)) {
        aio_value *new_value_2 = cast_to_string(value_2);
        return strcmp(value_1->get.string_acc, new_value_2->get.string_acc) < 0;
    } else {
        throw_error_with_hook(AIO_VALUE_TAG, "Can not compare values by type:", type_1);
    }
}

boolean is_less_or_equals_aio_value_then_other(aio_value *value_1, aio_value *value_2)
{
    if (!value_1) {
        if (!value_2) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else {
        if (!value_2) {
            return FALSE;
        }
    }
    const_str_hook *type_1 = value_1->type;
    if (is_hook_equals_str(type_1, INTEGER)) {
        aio_value *new_value_2 = cast_to_int(value_2);
        return value_1->get.int_acc <= new_value_2->get.int_acc;
    }
    if (is_hook_equals_str(type_1, DOUBLE)) {
        aio_value *new_value_2 = cast_to_double(value_2);
        return value_1->get.double_acc <= new_value_2->get.double_acc;
    }
    if (is_hook_equals_str(type_1, STRING)) {
        aio_value *new_value_2 = cast_to_string(value_2);
        return strcmp(value_1->get.string_acc, new_value_2->get.string_acc) <= 0;
    } else {
        throw_error_with_hook(AIO_VALUE_TAG, "Cannot compare values by type:", type_1);
    }
}
