#ifndef AIO_CORE_H
#define AIO_CORE_H

#define NUMBER_OF_CORE_TYPES 5

namespace lib4aio {

    template<class T>
    class array_list;

    class str_hook;
}

using namespace lib4aio;

class aio_bundle;

class aio_build_script;

class aio_runtime;

class aio_build_runtime;

class aio_program_runtime;

/**
 * 글로벌 핵심.
 */

class aio_core {

    friend class aio_context_inflater;

public:

    static aio_core *new_aio_core();

    aio_core *inflate_aio_config();

    aio_core *inflate_aio_context(const char *script_path);

    aio_core *invoke_aio_context(int argc, char *argv[]);

    void deflate();

private:

    explicit aio_core();

    ~aio_core();

    aio_build_runtime *build_runtime;

    aio_program_runtime *program_runtime;

    aio_bundle *new_main_bundle(
            const int argc,
            char **argv,
            const str_hook *file_path
    );
};

#endif //AIO_CORE_H