#include <cctype>
#include <cstring>
#include <lib4aio_cpp_headers/utils/point_watcher/point_watcher.h>
#include <lib4aio_cpp_headers/utils/memory_utils/memory_utils.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

namespace lib4aio
{

    str_hook::str_hook()
    {}

    str_hook::str_hook(const char *source_string, const unsigned start, const unsigned end)
    {
        this->source_string = source_string;
        this->start = start;
        this->end = end;
    }

    str_hook::str_hook(const char *source_string, const point_watcher *watcher)
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

    str_hook::str_hook(const char *source_string)
    {
        this->source_string = source_string;
        this->start = 0;
        this->end = (unsigned) strlen(source_string);
    }

    str_hook::~str_hook()
    {}

    unsigned str_hook::get_size() const
    {
        return this->end - this->start;
    }

    const char *str_hook::get_string() const
    {
        return this->source_string;
    }

    char str_hook::get_char(const int index) const
    {
        return this->source_string[index];
    }

    bool str_hook::equals_string(const str_hook *other) const
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

    bool str_hook::is_word() const
    {
        auto length = this->get_size();
        if (length < 1) {
            return false;
        }
        auto first_symbol = this->get_char(this->start);
        if (isalpha(first_symbol)) {
            if (length > 1) {
                for (int i = 1; i < length; ++i) {
                    auto symbol = this->get_char(i);
                    if (!isalnum(symbol)) {
                        return false;
                    }
                }
            }
            return true;
        } else {
            return false;
        }

    }

    bool str_hook::equals_string(const char *string) const
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

    bool str_hook::is_empty() const
    {
        return this->get_size() <= 0;
    }

    bool str_hook::is_not_empty() const
    {
        return this->get_size() > 0;
    }

    char *str_hook::to_string() const
    {
        char *string = (char *) new_object_array(this->get_size() + 1, sizeof(char));
        unsigned position = 0;
        for (unsigned i = this->start; i < this->end; ++i) {
            string[position++] = this->source_string[i];
        }
        return string;
    }

    void str_hook::set_string(const char *string)
    {
        this->source_string = string;
    }
}