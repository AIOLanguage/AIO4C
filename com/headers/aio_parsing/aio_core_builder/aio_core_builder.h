#ifndef AIO_CONTEXT_INFLATER_H
#define AIO_CONTEXT_INFLATER_H

namespace lib4aio {

    template<typename T>
    class array_list;

    class str_hook;
}

struct aio_file;

class aio_ray;

class aio_core;

using namespace lib4aio;

class aio_core_builder {

public:

    static aio_core_builder *create();

    aio_core_builder *set_core(aio_core *core);

    aio_core_builder *set_build_path(char *build_path);

    aio_core_builder *construct();

    void finish();

private:

    aio_core *core_ptr;

    char *build_path;

    void grub_aio_files();

    void grub_aio_file(const char *path);

    void construct_aio_files();
};

#endif //AIO_CONTEXT_INFLATER_H