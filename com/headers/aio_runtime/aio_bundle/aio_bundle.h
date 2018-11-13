#ifndef AIO_BUNDLE_H
#define AIO_BUNDLE_H

namespace lib4aio {

    struct struct_list;

    class str_hook;
}

class aio_core;

using namespace lib4aio;

struct aio_bundle {

    explicit aio_bundle();

    explicit aio_bundle(aio_core *core_ptr, str_hook *file_path, str_hook *function_name, struct_list *input_values);

    ~aio_bundle();

    aio_core *core_ptr;

    str_hook *file_path;

    str_hook *function_name;

    struct_list *input_values;

    struct_list *output_values;
};

#endif //AIO_BUNDLE_H