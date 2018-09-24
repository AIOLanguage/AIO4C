#ifndef AIO_BUNDLE_H
#define AIO_BUNDLE_H

namespace lib4aio {

    struct struct_list;

    class str_hook;
}

using namespace lib4aio;

class aio_runtime;

class aio_bundle {

public:

    aio_bundle(
            const aio_runtime *runtime_ptr,
            const str_hook *file_path,
            const str_hook *function_name,
            struct_list *input_values
    );

    const aio_runtime *const get_aio_runtime_ptr() const;

    const str_hook *get_file_path();

    const str_hook *get_function_name() const;

    const struct_list *get_input_values() const;

    const struct_list *get_output_values() const;

    ~aio_bundle();

private:

    const aio_runtime *runtime_ptr;

    const str_hook *file_path;

    const str_hook *function_name;

    struct_list *input_values;

    struct_list *output_values;

};

#endif //AIO_BUNDLE_H