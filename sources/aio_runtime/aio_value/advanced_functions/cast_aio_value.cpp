#include <aio_lang/aio_types/aio_types.h>
#include <aio_runtime/aio_value/aio_value.h>
#include <lib4aio_cpp_headers/utils/string_utils/cast.h>
#include <lib4aio_cpp_headers/utils/string_utils/match.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>

#define CAST_AIO_VALUE_TAG "CAST_AIO_VALUE"

using namespace lib4aio;

aio_value *cast_to_int(const aio_value *value)
{
    if (!value) {
        return nullptr;
    }
    auto type = value->type;
    if (type->equals_string(INTEGER)) {
        return new_aio_int_value(value->get.int_acc);
    } else if (type->equals_string(DOUBLE)) {
        return new_aio_int_value((int) value->get.double_acc);
    } else if (type->equals_string(STRING)) {
        auto string = value->get.string_acc;
        if (matches_int(string)) {
            return new_aio_int_value(string_to_int(string));
        } else if (matches_double(string)) {
            return new_aio_int_value((int) (string_to_double(string)));
        } else if (matches_boolean(string)) {
            return new_aio_int_value(string_to_boolean(string));
        } else {
            throw_error_with_details(CAST_AIO_VALUE_TAG, "String doesn't matches int!", string);
        }
    } else if (type->equals_string(BOOLEAN)) {
        return new_aio_int_value(value->get.boolean_acc);
    } else {
        throw_error_with_hook(CAST_AIO_VALUE_TAG, "Can not cast type to Int:", type);
    }
}

aio_value *cast_to_double(const aio_value *value)
{
    if (!value) {
        return nullptr;
    }
    auto type = value->type;
    if (type->equals_string(INTEGER)) {
        return new_aio_double_value(value->get.int_acc);
    } else if (type->equals_string(DOUBLE)) {
        return new_aio_double_value(value->get.double_acc);
    } else if (type->equals_string(STRING)) {
        auto string = value->get.string_acc;
        if (matches_int(string)) {
            return new_aio_double_value(string_to_int(string));
        } else if (matches_double(string)) {
            return new_aio_double_value(string_to_double(string));
        } else if (matches_boolean(string)) {
            return new_aio_double_value(string_to_boolean(string));
        } else {
            throw_error_with_details(CAST_AIO_VALUE_TAG, "String doesn't matches double!", string);
        }
    } else if (type->equals_string(BOOLEAN)) {
        return new_aio_double_value(value->get.boolean_acc);
    } else {
        throw_error_with_hook(CAST_AIO_VALUE_TAG, "Can not cast type to Dou:", type);
    }
}

aio_value *cast_to_string(const aio_value *value)
{
    if (!value) {
        return nullptr;
    }
    auto type = value->type;
    if (type->equals_string(INTEGER)) {
        return new_aio_string_value(int_to_string(value->get.int_acc));
    } else if (type->equals_string(DOUBLE)) {
        return new_aio_string_value(double_to_string(value->get.double_acc));
    } else if (type->equals_string(STRING)) {
        return new_aio_string_value(value->get.string_acc);
    } else if (type->equals_string(BOOLEAN)) {
        return new_aio_string_value(boolean_to_string(value->get.boolean_acc));
    } else {
        throw_error_with_hook(CAST_AIO_VALUE_TAG, "Can not cast type to Str:", type);
    }
}

aio_value *cast_to_boolean(const aio_value *value)
{
    if (!value) {
        return nullptr;
    }
    auto type = value->type;
    if (type->equals_string(INTEGER)) {
        auto int_value = value->get.int_acc;
        if (int_value == 1) {
            return new_aio_boolean_value(true);
        } else if (int_value == 0) {
            return new_aio_boolean_value(false);
        } else {
            throw_error_with_tag(CAST_AIO_VALUE_TAG, "Can not cast Int to Boo");
        }
    } else if (type->equals_string(DOUBLE)) {
        auto double_value = value->get.double_acc;
        if (double_value >= 0.5 && double_value <= 1.0) {
            return new_aio_boolean_value(true);
        } else if (double_value >= 0.0 && double_value < 0.5) {
            return new_aio_boolean_value(false);
        } else {
            throw_error_with_tag(CAST_AIO_VALUE_TAG, "Can not cast Dou to Boo");
        }
    } else if (type->equals_string(STRING)) {
        auto string_value = value->get.string_acc;
        if (matches_boolean(string_value)) {
            return new_aio_boolean_value(string_to_boolean(string_value));
        } else if (matches_int(string_value)) {
            auto int_value = string_to_int(string_value);
            if (int_value == 0) {
                return new_aio_boolean_value(false);
            } else if (int_value == 1) {
                return new_aio_boolean_value(true);
            } else {
                throw_error_with_tag(CAST_AIO_VALUE_TAG, "Can not cast Str to boolean");
            }
        } else if (matches_double(string_value)) {
            auto double_value = string_to_double(string_value);
            if (double_value >= 0.5 && double_value <= 1.0) {
                return new_aio_boolean_value(true);
            } else if (double_value >= 0.0 && double_value < 0.5) {
                return new_aio_boolean_value(false);
            } else {
                throw_error_with_tag(CAST_AIO_VALUE_TAG, "Can not cast Str to Boo");
            }
        } else if (matches_boolean(string_value)) {
            return new_aio_boolean_value(string_to_boolean(string_value));
        } else {
            throw_error_with_tag(CAST_AIO_VALUE_TAG, "Can not cast Str to Boo");
        }
    } else if (type->equals_string(BOOLEAN)) {
        return new_aio_boolean_value(value->get.boolean_acc);
    } else {
        throw_error_with_hook(CAST_AIO_VALUE_TAG, "Can not cast type to Boo:", type);
    }
}

aio_value *cast_to_void(const aio_value *value)
{
    if (!value) {
        return nullptr;
    }
    auto type = value->type;
    if (type->equals_string(INTEGER)) {
        return new_aio_int_value(value->get.int_acc);
    } else if (type->equals_string(DOUBLE)) {
        return new_aio_double_value(value->get.double_acc);
    } else if (type->equals_string(STRING)) {
        return new_aio_string_value(value->get.string_acc);
    } else if (type->equals_string(BOOLEAN)) {
        return new_aio_boolean_value(value->get.boolean_acc);
    } else {
        return new_aio_void_value(value->get.reference);
    }
}

aio_value *cast_to_type(
        const aio_value *value,
        const str_hook *type
)
{
    if (!value) {
        return nullptr;
    }
    if (type->equals_string(VOID)) {
        return cast_to_void(value);
    } else if (type->equals_string(INTEGER)) {
        return cast_to_int(value);
    } else if (type->equals_string(DOUBLE)) {
        return cast_to_double(value);
    } else if (type->equals_string(STRING)) {
        return cast_to_string(value);
    } else if (type->equals_string(BOOLEAN)) {
        return cast_to_boolean(value);
    } else {
        throw_error_with_hook(CAST_AIO_VALUE_TAG, "Sorry, AIO Core hasn't supported type:", type);
    }
}