#include <lib4aio_cpp_headers/utils/str_hook/str_hook.h>
#include <cstring>
#include <cctype>

namespace lib4aio
{

    /**
     * String hook.
     */

    str_hook::str_hook()
    {}

    str_hook::str_hook(char *source_string, const unsigned start, const unsigned end)
    {
        this->source_string = source_string;
        this->start = start;
        this->end = end;
    }

    str_hook::str_hook(char *source_string, const point_watcher *watcher)
    {
        this->source_string = source_string;
        this->start = watcher->start;
        this->end = watcher->end;
    }

    str_hook::str_hook(const str_hook *other)
    {
        this->source_string = other->source_string;
        this->start = other->start;
        this->end = other->end;
    }

    str_hook::str_hook(char *source_string)
    {
        this->source_string = source_string;
        this->start = 0;
        this->end = strlen(source_string);
    }

    str_hook::~str_hook()
    {}

    unsigned str_hook::get_size()
    {
        return this->end - this->start;
    }

    char str_hook::get_char(const int index)
    {
        return this->source_string[index];
    }

    bool str_hook::hooks_equal_string(str_hook *other)
    {
        auto size_1 = this->get_size();
        auto size_2 = other->get_size();
        if (size_1 != size_2) {
            return false;
        }
        auto str_1 = this->source_string;
        auto str_2 = other->source_string;
        auto start_1 = this->start;
        auto start_2 = other->start;
        for (int i = 0; i < size_1; ++i) {
            if (str_1[start_1 + i] != str_2[start_2 + i]) {
                return false;
            }
        }
        return true;
    }

    bool str_hook::is_word()
    {
        auto length = this->get_size();
        if (length < 1) {
            return false;
        }
        auto first_symbol = this->get_char(0);
        if (isalpha(first_symbol)) {
            if (length > 1) {
                for (int i = 1; i < length; ++i) {
                    auto symbol = this->get_char(i);
                    if (!isalnum(symbol)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool str_hook::hooks_equal_string(const char *string)
    {
        auto hook_size = this->get_size();
        auto str_length = strlen(string);
        if (hook_size != str_length) {
            return false;
        }
        auto hooked_string = this->source_string;
        auto start = this->start;
        for (int i = 0; i < hook_size; ++i) {
            if (hooked_string[start + i] != string[i]) {
                return false;
            }
        }
        return true;
    }

    bool str_hook::is_empty()
    {
        return this->get_size() <= 0;
    }

    bool str_hook::is_not_empty()
    {
        return this->get_size() > 0;
    }



































///**
// * List.
// */
//
//    str_hook_list *new_str_hook_list()
//    {
//        str_hook_list *list = new_object(sizeof(str_hook_list));
//        list->capacity = INIT_CAPACITY;
//        list->size = 0;
//        list->hooks = new_object_array(INIT_CAPACITY, sizeof(str_hook));
//        return list;
//    }
//
//    static void update_memory_in_string_hook_list(str_hook_list *list)
//    {
//        if (list->size == list->capacity) {
//            list->capacity *= INIT_CAPACITY;
//            list->hooks = reallocate_object_array(list->hooks, list->capacity, sizeof(str_hook));
//        }
//    }
//
//    void add_str_hook_in_list(str_hook_list *list, str_hook *hook)
//    {
//        update_memory_in_string_hook_list(list);
//        list->hooks[list->size] = hook;
//        list->size++;
//    }
//
//    void free_str_hooks_in_list(str_hook_list *list)
//    {
//        str_hook **hooks = list->hooks;
//        for (int i = 0; i < list->size; ++i) {
//            free_str_hook(hooks[i]);
//        }
//    }
//
//    void reset_str_hook_positions(str_hook *hook)
//    {
//        hook->start = 0;
//        hook->end = 0;
//    }
//
//    void free_str_hook_list(str_hook_list *list)
//    {
//        str_hook **hooks = list->hooks;
//        free(hooks);
//        free((void *) list);
//    }
//
///**
// * String hook iterator.
// */
//
//
//    str_hook_iterator *new_str_hook_iterator()
//    {
//        str_hook_iterator *iterator = new_object(sizeof(str_hook_iterator));
//        iterator->position = 0;
//        return iterator;
//    }
//
//    str_hook_iterator *new_str_hook_iterator_by_list(
//            str_hook_list *str_hook_list,
//            const unsigned current_hook_index
//    )
//    {
//        val start_position = str_hook_list->hooks[current_hook_index]->start;
//        //Create iterator:
//        str_hook_iterator *iterator = new_object(sizeof(str_hook_iterator));
//        iterator->str_hook_list = str_hook_list;
//        iterator->current_hook_index = current_hook_index;
//        iterator->position = start_position;
//        return iterator;
//    }
//
//    boolean next_in_str_hook_iterator(str_hook_iterator *iterator)
//    {
//        //Extract list:
//        str_hook_list *list = iterator->str_hook_list;
//        str_hook **hooks = list->hooks;
//        //Get current hook:
//        const unsigned current_hook_index = iterator->current_hook_index;
//        str_hook *current_hook = hooks[current_hook_index];
//        //Check next position:
//        if (iterator->position < current_hook->end - 1) {
//            iterator->position++;
//            return TRUE;
//        } else {
//            if (current_hook_index < list->size - 1) {
//                iterator->position = hooks[++iterator->current_hook_index]->start;
//                return TRUE;
//            } else {
//                return FALSE;
//            }
//        }
//    }
//
//    void free_str_hook_iterator(str_hook_iterator *iterator)
//    {
//        if (iterator) {
//            free(iterator);
//        }
//    }
}