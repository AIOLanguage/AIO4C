#ifndef AIO_AIO_EXPRESSION_PARSER_H
#define AIO_AIO_EXPRESSION_PARSER_H

/**
 * Root parsers.
 */

 //FIXME: UNUSED ARG CONTEXT:
struct aio_value *parse_value_string(
        const char *expression_string,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph
);

struct aio_value *parse_value_hook(
        const struct str_hook *expression_hook,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph
);

/**
 * Expression assistant.
 */

struct aio_result *make_parentheses(
        const struct str_hook *expression_hook,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph,
        struct aio_value *(*cast_function)(struct aio_value *),
        struct aio_result *(*make_value_function)(const struct str_hook *)
);

void make_expression_chunks_and_count_next_point(
        const struct str_hook *expression_hook,
        struct str_hook_list *expression_list,
        int *next_point
);

struct aio_result *make_function_or_variable(
        const struct str_hook *expression_hook,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph,
        struct aio_value *(*cast_function)(struct aio_value *),
        struct aio_result *(*make_value_function)(const struct str_hook *)
);

/**
 * Inner parsers.
 */

struct aio_value *parse_int_value_string(
        const struct str_hook *expression_hook,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph
);

struct aio_value *parse_double_value_string(
        const struct str_hook *expression_hook,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph
);

struct aio_value *parse_string_value_string(
        const struct str_hook *expression_hook,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph
);

struct aio_value *parse_boolean_value_string(
        const struct str_hook *expression_hook,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph
);

struct aio_value *parse_type_value_string(
        const struct str_hook *expression_hook,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph
);

struct aio_value *parse_void_value_string(
        const struct str_hook *expression_hook,
        const struct aio_context *context,
        const struct aio_function_control_graph *control_graph
);

#endif //AIO_AIO_EXPRESSION_PARSER_H