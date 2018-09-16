#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>

namespace lib4aio
{
#ifndef LIB4AIO_STR_HOOK_LIST_H
#define LIB4AIO_STR_HOOK_LIST_H

    class str_hook_list : public array_list<str_hook>
    {

    private:

    public:

        str_hook_list();

        str_hook_list *trim() const;

        str_hook_list *trim_with_line_break() const;
    };

    void log_info(const char *const tag, const char *message, const str_hook_list *list);

    /**
     * Typedef utils.
     */

    typedef str_hook_list str_hook_chain;

#endif //LIB4AIO_STR_HOOK_LIST_H
}