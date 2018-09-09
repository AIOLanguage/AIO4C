void log_info_aio_value(const_string tag, string message, const aio_value *value)
{
    if (value) {
        const_str_hook *type = value->type;
        if (is_hook_equals_str(type, INTEGER)) {
            log_info_int(tag, message, value->get.int_acc);
        } else if (is_hook_equals_str(type, DOUBLE)) {
            log_info_double(tag, message, value->get.double_acc);
        } else if (is_hook_equals_str(type, STRING)) {
            log_info_string(tag, message, value->get.string_acc);
        } else if (is_hook_equals_str(type, BOOLEAN)) {
            log_info_boolean(tag, message, value->get.boolean_acc);
        } else {
            log_info_string(tag, message, "Can not log void reference!");
        }
    } else {
        log_info_string(tag, message, "NULL");
    }
}