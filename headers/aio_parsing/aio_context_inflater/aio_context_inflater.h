#ifndef AIO_CONTEXT_INFLATER_H
#define AIO_CONTEXT_INFLATER_H

namespace lib4aio {

    class str_hook;
}

using namespace lib4aio;

class aio_core;

class aio_context_inflater {

public:

    aio_context_inflater(aio_core *core, const char *script_path);

    void inflate();

    ~aio_context_inflater();

private:

    aio_core *core;

    const char *script_path;

    void inflate_aio_build_script();

    void inflate_aio_files();

    void inflate_aio_file(const str_hook *relative_file_path, const char *script_path);
};

#endif //AIO_CONTEXT_INFLATER_H