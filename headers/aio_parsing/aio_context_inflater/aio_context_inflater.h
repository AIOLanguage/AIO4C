#ifndef AIO_CONTEXT_INFLATER_H
#define AIO_CONTEXT_INFLATER_H

namespace lib4aio {

    template<typename T>
    class array_list;

    class str_hook;
}

using namespace lib4aio;

class aio_core;

class aio_file;

class aio_runtime;

class aio_ray;

class aio_context_inflater {

public:

    static aio_context_inflater *create();

    aio_context_inflater *set_core(aio_core *core);

    aio_context_inflater *set_script_path(const char *script_path);

    aio_context_inflater *inflate();

    void destroy();

private:

    aio_core *core;

    const char *script_path;

    void inflate_aio_file(const char *root_path, aio_runtime *runtime);

    void inflate_aio_build_script();

    void invoke_aio_build_script();

    void inflate_aio_program();

    void inflate_aio_file(
            const str_hook *relative_file_path,
            const char *script_path,
            aio_runtime *runtime
    );
};

#endif //AIO_CONTEXT_INFLATER_H