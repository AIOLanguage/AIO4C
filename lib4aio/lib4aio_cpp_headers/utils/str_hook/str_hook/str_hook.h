namespace lib4aio
{

#ifndef LIB4AIO_STRING_HOOK_H
#define LIB4AIO_STRING_HOOK_H

    /**
     * Declare classes.
     */

    class str_hook_list;

    class point_watcher;

    class str_hook
    {

    public:

        unsigned start;

        unsigned end;

        const char *source_string;

        /**
         * Constructors & destructor.
         */

        str_hook();

        str_hook(const char *source_string, const unsigned start, const unsigned end);

        str_hook(const char *source_string, const point_watcher *const watcher);

        str_hook(const str_hook *other);

        str_hook(const char *source_string);

        ~str_hook();

        /**
         * Functions.
         */

        unsigned get_size() const;

        const char *get_string() const;

        char get_char(const int index) const;

        bool is_word() const;

        bool equals_string(const str_hook *const other) const;

        bool equals_string(const char *const string) const;

        bool is_empty() const;

        bool is_not_empty() const;

        str_hook_list *split(const char *const delimiter) const;

        str_hook_list *split_by_comma() const;

        str_hook_list *split_by_space() const;

        str_hook_list *split_by_line_break() const;

        str_hook_list *split_by_whitespace() const;

        str_hook_list *split_by_char_condition(bool (*char_condition)(const char)) const;

        str_hook *trim_by_start() const;

        str_hook *trim_by_end() const;

        str_hook *trim() const;

        str_hook *trim_with_line_break_by_start() const;

        str_hook *trim_with_line_break_by_end() const;

        str_hook *trim_with_line_break() const;

        /**
        * Primitive type matchers.
        */

        bool matches_int() const;

        bool matches_double() const ;

        bool matches_string() const ;

        bool matches_boolean() const ;

        /**
        * Casts.
        */

        int to_int() const;

        double to_double() const;

        str_hook *lower_quotes() const;

        bool to_boolean() const;
    };

    void log_info(const char *tag, const char *message, const str_hook *hook);

    void throw_error(const char *tag, const char *message, const str_hook *hook) __attribute__ ((noreturn));

#endif //LIB4AIO_STRING_HOOK_H

}