#ifndef AIO_CONTEXT_CONTROL_GRAPH_H
#define AIO_CONTEXT_CONTROL_GRAPH_H

typedef struct aio_context_control_graph {
    struct aio_field_list *field_list;
    struct aio_context_instruction_list *instruction_list;
    struct aio_bundle *bundle;
} aio_context_control_graph;

#endif //AIO_CONTEXT_CONTROL_GRAPH_H