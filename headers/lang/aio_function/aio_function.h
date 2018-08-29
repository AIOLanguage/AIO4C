#ifndef AIO_FUNCTION_H
#define AIO_FUNCTION_H

struct aio_value_list *invoke_static_function_in_context(
        const struct aio_context *context,
        const struct str_hook *function_name,
        struct aio_bundle *bundle
);

struct aio_value_list *invoke_aio_function(
        const struct aio_function_definition *definition,
        struct aio_bundle *bundle,
        const struct aio_context *context
);

#endif //AIO_FUNCTION_H