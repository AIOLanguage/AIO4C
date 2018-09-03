#ifndef AIO_FUNCTION_CONTROL_GRAPH_H
#define AIO_FUNCTION_CONTROL_GRAPH_H

/**
 * Linking.
 */

typedef enum aio_function_system_state {
    AIO_FUNCTION_SYSTEM_MAKE, AIO_FUNCTION_SYSTEM_BREAK, AIO_FUNCTION_SYSTEM_CONTINUE, AIO_FUNCTION_SYSTEM_STOP
} aio_function_system_state;


typedef struct aio_function_control_graph {
    struct aio_function_control_graph *parent;
    struct aio_field_list *field_list;
    struct aio_function_instruction_list *instruction_list;
    struct aio_bundle *bundle;
    enum aio_function_system_state *system_state_ref;
} aio_function_control_graph;

struct aio_function_control_graph *new_aio_function_control_graph(
        struct aio_function_control_graph *parent,
        struct aio_function_instruction_holder *holder,
        struct aio_bundle *bundle,
        enum aio_function_system_state *system_state_ref
);

void inflate_new_aio_function_control_graph(
        struct aio_function_control_graph *parent,
        struct aio_function_instruction_holder *holder,
        struct aio_bundle *bundle
);

void inflate_new_aio_root_function_control_graph(
        struct aio_function_control_graph *parent,
        struct aio_function_definition *function_definition,
        struct aio_bundle *bundle
);

void perform_aio_function_instructions(struct aio_function_control_graph *control_graph);

void free_aio_control_graph(struct aio_function_control_graph *graph);

#endif //AIO_FUNCTION_CONTROL_GRAPH_H