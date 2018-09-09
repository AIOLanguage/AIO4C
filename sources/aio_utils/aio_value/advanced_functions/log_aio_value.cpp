#include <aio_utils/aio_value/aio_value.h>
#include <lib4aio_cpp_headers/utils/string_utils/common.h>
#include <aio_lang/aio_types/aio_type.h>
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>

void log_info_aio_value(
        const_string tag,
        const_string message,
        const aio_value *value
)
{
    if (value) {
        auto type = value->type;
        if (type->equals_string(INTEGER)) {
            log_info_int(tag, message, value->get.int_acc);
        } else if (type->equals_string(DOUBLE)) {
            log_info_double(tag, message, value->get.double_acc);
        } else if (type->equals_string(STRING)) {
            log_info_string(tag, message, value->get.string_acc);
        } else if (type->equals_string(BOOLEAN)) {
            log_info_boolean(tag, message, value->get.boolean_acc);
        } else {
            log_info_string(tag, message, "Can not log void reference!");
        }
    } else {
        log_info_string(tag, message, "NULL");
    }
}