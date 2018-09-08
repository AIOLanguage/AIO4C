#include <lib4aio_cpp_headers/utils/str_hook/str_hook/str_hook.h>

namespace lib4aio
{
#ifndef LIB4AIO_STR_HOOK_LIST_H
#define LIB4AIO_STR_HOOK_LIST_H

    class str_hook_list
    {

    private:

        unsigned capacity;

        unsigned size;

        str_hook **hooks;

        void update_memory();

    public:

        str_hook_list();

        ~str_hook_list();

        unsigned get_size() const ;

        str_hook *get(const int position) const;

        void add(str_hook *hook);

        str_hook_list *trim() const;

        str_hook_list *trim_with_line_break() const;

        str_hook_list *filter(bool (*filter_condition)(const class str_hook *)) const;

        void foreach(void (*str_hook_action)(const class str_hook *hook)) const;

        void free_str_hooks();
    };

    void log_info(const char *const tag, const char *message, const str_hook_list *list);

#endif //LIB4AIO_STR_HOOK_LIST_H
}