#include <lib4aio_cpp_headers/utils/str_hook/str_hook_list/str_hook_list.h>

namespace lib4aio
{
    str_hook_list *str_hook_list::trim() const
    {
        auto hooks = this->hooks;
        auto new_list = new str_hook_list();
        auto list_size = this->size;
        for (int i = 0; i < list_size; ++i) {
            auto new_hook = hooks[i]->trim();
            new_list->add(new_hook);
        }
        return new_list;
    }

    str_hook_list *str_hook_list::trim_with_line_break() const
    {
        auto hooks = this->hooks;
        auto new_list = new str_hook_list();
        auto list_size = this->size;
        for (int i = 0; i < list_size; ++i) {
            auto new_hook = hooks[i]->trim();
            new_list->add(new_hook);
        }
        return new_list;
    }
}