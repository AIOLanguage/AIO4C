#ifndef AIO_AIO_FUNCTION_CONTROL_GRAPH_MANAGEMENT_H
#define AIO_AIO_FUNCTION_CONTROL_GRAPH_MANAGEMENT_H

struct aio_variable *force_get_aio_variable_in_function_control_graph(
        const struct str_hook *variable_name,
        const struct aio_function_control_graph *control_graph
);

struct aio_variable *get_aio_variable_in_function_control_graph(
        const struct str_hook *variable_name,
        const struct aio_function_control_graph *control_graph
);

void put_arg_values_in_aio_control_graph(
        const struct aio_function_control_graph *control_graph,
        const struct aio_function_definition *function_definition
);

#endif //AIO_AIO_FUNCTION_CONTROL_GRAPH_MANAGEMENT_H