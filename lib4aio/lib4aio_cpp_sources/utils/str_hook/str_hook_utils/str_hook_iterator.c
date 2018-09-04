#include "../../../../../headers/lib/utils/str_hook/str_hook.h"

void foreach_str_hook(const_str_hook_list *list, void (*str_hook_action)(const_str_hook *))
{
    const_str_hook_array hooks = list->hooks;
    for (int i = 0; i < list->size; ++i) {
        str_hook_action(hooks[i]);
    }
}