#include <lib4aio_cpp_headers/utils/point_watcher/point_watcher.h>

namespace lib4aio
{

#ifndef STRING_HOOK_H
#define STRING_HOOK_H

    class str_hook_list;

/**
 * String hook.
 */

    class str_hook
    {

    private:

        char *source_string;


    public:

        unsigned start;

        unsigned end;

        /**
         * Constructors & destructor.
         */

        str_hook();

        str_hook(char *source_string, const unsigned start, const unsigned end);

        str_hook(char *source_string, const point_watcher *watcher);

        str_hook(const str_hook *other);

        str_hook(char *source_string);

        ~str_hook();

        /**
         * Functions.
         */

        unsigned get_size();

        char get_char(const int index);

        bool hooks_equal_string(str_hook *other);

        bool is_word();

        bool hooks_equal_string(const char *string);

        bool is_empty();

        bool is_not_empty();

        str_hook_list *split(const char *delimiter);

        str_hook_list *split_by_comma();

        str_hook_list *split_by_space();

        str_hook_list *split_by_line_break();

        str_hook_list *split_by_whitespace();

        str_hook_list *split_by_char_condition(bool (*char_condition)(const char));

        str_hook *trim_by_start();

        str_hook *trim_by_end();

        str_hook *trim();

        str_hook *trim_with_line_break_by_start();

        str_hook *trim_with_line_break_by_end();

        str_hook *trim_with_line_break();

        void log_info_str_hook(const char *tag, const char *message, const struct str_hook *hook);

        void throw_error_with_hook(const char *tag, const char *message);

        /**
        * Primitive type matchers.
        */

        bool matches_int();

        bool matches_double();

        bool matches_string();

        bool matches_boolean();

        bool matches_null();

        /**
        * Sign.
        */

        bool matches_more_or_equal_sign(const int current_index);

        bool matches_less_or_equal_sign(const int current_index);

        bool mathces_double_equal_sign(const int current_index);

        /**
        * Casts.
        */

        int to_int();

        double to_double();

        str_hook *lower_quotes();

        bool to_boolean();
    };

    /**
    * List.
    */

    class str_hook_list
    {
    private:

        unsigned capacity;

        unsigned size;

        str_hook **hooks;

    public:

        str_hook_list();

        ~str_hook_list();

        void add(str_hook *hook);

        str_hook_list *trim();

        str_hook_list *trim_with_line_break();

        str_hook_list *filter(bool (*filter_condition)(const struct str_hook *));

        void foreach(void (*str_hook_action)(const struct str_hook *hook));

        void log_info(const char *tag, const char *message);

        void free_str_hooks();
    };

    /**
    * String hook iterator.
    */

    class str_hook_iterator
    {
    private:

        str_hook_list *list;

        unsigned current_hook_index;

        unsigned hook_position;

    public:

        str_hook_iterator();

        str_hook_iterator(str_hook_list *list);

        str_hook_iterator(str_hook_list *list, str_hook *current_hook);

        str_hook_iterator(str_hook_list *list, str_hook *current_hook, const unsigned current_position);

        bool next();

        ~str_hook_iterator();

    };

#endif //STRING_HOOK_H

}