#include <lib4aio_cpp_headers/utils/memory_utils/memory_utils.h>
#include <lib4aio_cpp_headers/utils/str_hook/str_hook/str_hook.h>
#include <lib4aio_cpp_headers/utils/str_hook/str_hook_list/str_hook_list.h>

namespace lib4aio
{

    str_hook_list::str_hook_list()
    {
        this->capacity = INIT_CAPACITY;
        this->size = 0;
        this->hooks = static_cast<str_hook **>(new_object_array(INIT_CAPACITY, sizeof(str_hook)));
    }

    void str_hook_list::update_memory()
    {
        if (this->size == this->capacity) {
            this->capacity *= INIT_CAPACITY;
            this->hooks = static_cast<str_hook **>(reallocate_object_array(
                    this->hooks,
                    this->capacity,
                    sizeof(str_hook))
            );
        }
    }

    void str_hook_list::add(str_hook *hook)
    {
        this->update_memory();
        this->hooks[this->size++] = hook;
    }

    str_hook *str_hook_list::get(const int position) const
    {
        return this->hooks[position];
    }

    unsigned str_hook_list::get_size() const
    {
        return this->size;
    }

    str_hook_list *str_hook_list::filter(bool (*filter_condition)(const str_hook *)) const
    {
        auto src_list_size = this->size;
        auto src_hooks = this->hooks;
        auto new_hook_list = new str_hook_list();
        for (int k = 0; k < src_list_size; ++k) {
            auto src_hook = src_hooks[k];
            if (filter_condition(src_hook)) {
                auto new_hook = new str_hook(src_hook);
                new_hook_list->add(new_hook);
            }
        }
        return new_hook_list;
    }

    void str_hook_list::foreach(void (*str_hook_action)(const struct str_hook *hook)) const
    {
        auto size = this->size;
        auto hooks = this->hooks;
        for (unsigned i = 0; i < size; ++i) {
            str_hook_action(hooks[i]);
        }
    }

    void str_hook_list::free_str_hooks()
    {
        auto size = this->size;
        auto hooks = this->hooks;
        for (unsigned i = 0; i < size; ++i) {
            delete hooks[i];
        }
    }

    str_hook_list::~str_hook_list()
    {
        delete this->hooks;
    }
}