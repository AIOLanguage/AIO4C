#ifndef AIO_STR_HOOK_CAPTURE_H
#define AIO_STR_HOOK_CAPTURE_H

namespace lib4aio {

    class str_hook;
}

using namespace lib4aio;

bool is_int_hooked(const str_hook *hook);

bool is_double_hooked(const str_hook *hook);

bool is_string_hooked(const str_hook *hook);

bool is_boolean_hooked(const str_hook *hook);

#endif //AIO_STR_HOOK_CAPTURE_H