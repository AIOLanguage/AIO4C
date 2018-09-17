#ifndef AIO_BUNDLE_H
#define AIO_BUNDLE_H

#include <lib4aio_cpp_headers/utils/struct_list/struct_list.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

using namespace lib4aio;

class aio_bundle {

public:

    aio_bundle(str_hook *function_name, struct struct_list *input_values);

    const str_hook *get_function_name() const;

    const struct_list *get_input_values() const;

    const struct_list *get_output_values() const;

    ~aio_bundle();

private:

    str_hook *function_name;

    struct_list *input_values;

    struct_list *output_values;

};

#endif //AIO_BUNDLE_H