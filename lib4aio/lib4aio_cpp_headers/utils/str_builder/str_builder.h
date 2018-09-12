namespace lib4aio
{

#ifndef LIB4AIO_STR_BUILDER_H
#define LIB4AIO_STR_BUILDER_H

    class str_builder
    {
    private:

        char *string_value;

        unsigned capacity;

        unsigned length;

        void grow(const unsigned range);

    public:

        str_builder();

        void append(const char c);

        void append(const char *string);

        char *pop();

        void reset();

        const char *get_string() const;

        unsigned size() const;

        ~str_builder();
    };

#endif //LIB4AIO_STR_BUILDER_H

}