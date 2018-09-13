#ifndef AIO_BUNDLE_H
#define AIO_BUNDLE_H

/**
 * Linking.
 */

#include <lib4aio_cpp_headers/utils/struct_list/struct_list.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

using namespace lib4aio;

class aio_bundle
{

private:

    lib4aio::str_hook *function_name;

public:

    struct struct_list *input_values;

    struct struct_list *output_values;

    aio_bundle(
            lib4aio::str_hook *function_name,
            struct struct_list *input_values
    );

    const lib4aio::str_hook *get_function_name() const;

    ~aio_bundle();
};

#endif //AIO_BUNDLE_H
