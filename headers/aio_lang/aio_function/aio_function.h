#ifndef AIO_FUNCTION_H
#define AIO_FUNCTION_H

struct aio_value_list *invoke_static_function_in_context(
        struct str_hook *function_name,
        struct aio_bundle *bundle
);

struct aio_value_list *invoke_aio_function(
        struct aio_function_definition *definition,
        struct aio_bundle *bundle
);

#endif //AIO_FUNCTION_H