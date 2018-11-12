#ifndef AIO_EXPRESSION_PARSER_H
#define AIO_EXPRESSION_PARSER_H

namespace lib4aio {

    class str_hook;
}

using namespace lib4aio;

struct aio_value;

struct aio_result;

class aio_ray;

class aio_expression_parser {

public:

    /**
    * Parses string expression.
    * @param expression_string
    * @param ray
    * @return value.
    */

    static aio_value *parse(const char *expression, aio_ray *ray);

    /**
    * Parses expression hook.
    * @param expression_hook
    * @param ray
    * @return value.
    */

    static aio_value *parse(const str_hook *expression, aio_ray *ray);

private:

    class aio_analyser {

    public:

        static const str_hook *define_expression_type(const str_hook *expression, aio_ray *ray);
    };

    class aio_int_parser {

    public:

        static aio_value *parse(const str_hook *expression, aio_ray *ray);

    private:

        static aio_result *make_plus_or_minus(const str_hook *expression, aio_ray *ray);

        static aio_result *make_multiplication_or_division_or_mod(const str_hook *expression, aio_ray *ray);

        static aio_result *make_int(const str_hook *expression_hook);
    };

    class aio_double_parser {

    public:

        static aio_value *parse(const str_hook *expression, aio_ray *ray);
    };

    class aio_string_parser {

    public:

        static aio_value *parse(const str_hook *expression, aio_ray *ray);
    };

    class aio_boolean_parser {

    public:

        static aio_value *parse(const str_hook *expression, aio_ray *ray);
    };
};

#endif //AIO_EXPRESSION_PARSER_H