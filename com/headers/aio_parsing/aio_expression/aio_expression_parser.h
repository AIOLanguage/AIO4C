#ifndef AIO_EXPRESSION_PARSER_H
#define AIO_EXPRESSION_PARSER_H

namespace lib4aio {

    class str_hook;

    class str_hook_list;
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

    class aio_assistant {

    public:

        static aio_result *make_parentheses(
                const str_hook *expression_hook,
                aio_ray *control_graph,
                aio_value *(*cast_function)(const aio_value *),
                aio_result *(*make_value_function)(const str_hook *)
        );

    private:

        static aio_result *make_function_or_variable(
                const str_hook *expression_hook,
                aio_ray *control_graph,
                aio_value *(*cast_function)(aio_value *),
                aio_result *(*make_value_function)(const str_hook *)
        );

        static void make_expression_chunks_and_count_next_point(
                const str_hook *expression_hook,
                str_hook_list *expression_list,
                unsigned *next_point
        );
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

    private:

        static aio_result *make_plus_or_minus(const str_hook *expression, aio_ray *ray);

        static aio_result *make_multiplication_or_division(const str_hook *expression, aio_ray *ray);

        static aio_result *make_double(const str_hook *expression);
    };

    class aio_string_parser {

    public:

        static aio_value *parse(const str_hook *expression, aio_ray *ray);

    private:

        static aio_result *make_plus(const str_hook *expression, aio_ray *ray);

        static aio_result *make_string(const str_hook *expression);
    };

    class aio_boolean_parser {

    public:

        static aio_value *parse(const str_hook *expression, aio_ray *ray);
    };
};

#endif //AIO_EXPRESSION_PARSER_H