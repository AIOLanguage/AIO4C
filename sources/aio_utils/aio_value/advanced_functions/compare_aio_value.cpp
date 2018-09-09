#include <cstring>
#include <aio_lang/aio_types/aio_type.h>
#include <aio_utils/aio_value/aio_value.h>
#include <aio_utils/aio_value/advanced_functions/cast_aio_value.h>
#include <lib4aio_cpp_headers/utils/string_utils/common.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>

#define COMPARE_AIO_VALUE_TAG "COMPARE_AIO_VALUE"

bool are_equal_aio_values(
        const aio_value *value_1,
        const aio_value *value_2
)
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
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return are_equal;
    } else if (type_1->equals_string(DOUBLE)) {
        auto new_value_2 = cast_to_double(value_2);
        auto are_equal = value_1->get.double_acc == new_value_2->get.double_acc;
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return are_equal;
    } else if (type_1->equals_string(STRING)) {
        auto new_value_2 = cast_to_string(value_2);
        auto are_equal = are_equal_strings(value_1->get.string_acc, new_value_2->get.string_acc);
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return are_equal;
    } else if (type_1->equals_string(BOOLEAN)) {
        auto new_value_2 = cast_to_boolean(value_2);
        auto are_equal = value_1->get.boolean_acc == new_value_2->get.boolean_acc;
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return are_equal;
    } else {
        //Compare references:
        auto are_equal = value_1->get.reference == value_2->get.reference;
        return are_equal;
    }
}

bool are_not_equal_aio_values(
        const aio_value *value_1,
        const aio_value *value_2
)
{
    if (!value_1) {
        return value_2 != nullptr;
    } else {
        if (!value_2) {
            return true;
        }
    }
    auto type_1 = value_1->type;
    if (type_1->equals_string(INTEGER)) {
        auto new_value_2 = cast_to_int(value_2);
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return value_1->get.int_acc != new_value_2->get.int_acc;
    } else if (type_1->equals_string(DOUBLE)) {
        auto new_value_2 = cast_to_double(value_2);
        auto are_not_equal = value_1->get.double_acc != new_value_2->get.double_acc;
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return are_not_equal;
    } else if (type_1->equals_string(STRING)) {
        auto new_value_2 = cast_to_string(value_2);
        auto are_not_equal = !are_equal_strings(value_1->get.string_acc, new_value_2->get.string_acc);
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return are_not_equal;
    } else if (type_1->equals_string(BOOLEAN)) {
        auto new_value_2 = cast_to_boolean(value_2);
        auto are_not_equal = value_1->get.boolean_acc != new_value_2->get.boolean_acc;
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return are_not_equal;
    } else {
        return value_1->get.reference != value_2->get.reference;
    }
}

bool is_more_aio_value_then_other(
        const aio_value *value_1,
        const aio_value *value_2
)
{
    if (!value_1) {
        throw_error_with_tag(COMPARE_AIO_VALUE_TAG, "Left value is null!");
    }
    if (!value_2) {
        throw_error_with_tag(COMPARE_AIO_VALUE_TAG, "Right value is null!");
    }
    auto type_1 = value_1->type;
    if (type_1->equals_string(INTEGER)) {
        auto new_value_2 = cast_to_int(value_2);
        auto is_more = value_1->get.int_acc > new_value_2->get.int_acc;
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return is_more;
    } else if (type_1->equals_string(DOUBLE)) {
        auto new_value_2 = cast_to_double(value_2);
        auto is_more = value_1->get.double_acc > new_value_2->get.double_acc;
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return is_more;
    } else if (type_1->equals_string(STRING)) {
        auto new_value_2 = cast_to_string(value_2);
        auto is_more = strcmp(value_1->get.string_acc, new_value_2->get.string_acc) > 0;
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return is_more;
    } else {
        throw_error_with_hook(COMPARE_AIO_VALUE_TAG, "Can not compare values by type:", type_1);
    }
}

bool is_more_or_equals_aio_value_then_other(
        const aio_value *value_1,
        const aio_value *value_2
)
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
        auto is_more_or_equals = value_1->get.int_acc >= new_value_2->get.int_acc;
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return is_more_or_equals;
    } else if (type_1->equals_string(DOUBLE)) {
        auto new_value_2 = cast_to_double(value_2);
        auto is_more_or_equals = value_1->get.double_acc >= new_value_2->get.double_acc;
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return is_more_or_equals;
    } else if (type_1->equals_string(STRING)) {
        auto new_value_2 = cast_to_string(value_2);
        auto is_more_or_equals = strcmp(value_1->get.string_acc, new_value_2->get.string_acc) >= 0;
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return is_more_or_equals;
    } else {
        throw_error_with_hook(COMPARE_AIO_VALUE_TAG, "Can not compare values by type:", type_1);
    }
}

bool is_less_aio_value_then_other(
        const aio_value *value_1,
        const aio_value *value_2
)
{
    if (!value_1) {
        throw_error_with_tag(COMPARE_AIO_VALUE_TAG, "Left value is null!");
    }
    if (!value_2) {
        throw_error_with_tag(COMPARE_AIO_VALUE_TAG, "Right value is null!");
    }
    auto type_1 = value_1->type;
    if (type_1->equals_string(INTEGER)) {
        auto new_value_2 = cast_to_int(value_2);
        auto is_less = value_1->get.int_acc < new_value_2->get.int_acc;
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return is_less;
    } else if (type_1->equals_string(DOUBLE)) {
        auto new_value_2 = cast_to_double(value_2);
        auto is_less = value_1->get.double_acc < new_value_2->get.double_acc;
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return is_less;
    } else if (type_1->equals_string(STRING)) {
        auto new_value_2 = cast_to_string(value_2);
        auto is_less = strcmp(value_1->get.string_acc, new_value_2->get.string_acc) < 0;
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return is_less;
    } else {
        throw_error_with_hook(COMPARE_AIO_VALUE_TAG, "Can not compare values by type:", type_1);
    }
}

bool is_less_or_equals_aio_value_then_other(
        const aio_value *value_1,
        const aio_value *value_2
)
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
        auto is_less_or_equals = value_1->get.int_acc <= new_value_2->get.int_acc;
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return is_less_or_equals;
    } else if (type_1->equals_string(DOUBLE)) {
        auto new_value_2 = cast_to_double(value_2);
        auto is_less_or_equals = value_1->get.double_acc <= new_value_2->get.double_acc;
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return is_less_or_equals;
    } else if (type_1->equals_string(STRING)) {
        auto new_value_2 = cast_to_string(value_2);
        auto is_less_or_equals = strcmp(value_1->get.string_acc, new_value_2->get.string_acc) <= 0;
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집:
        free_aio_value(new_value_2);
        //--------------------------------------------------------------------------------------------------------------
        return is_less_or_equals;
    } else {
        throw_error_with_hook(COMPARE_AIO_VALUE_TAG, "Can not compare values by type:", type_1);
    }
}