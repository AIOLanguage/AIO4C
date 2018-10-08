#ifndef AIO_CORE_H
#define AIO_CORE_H

#define NUMBER_OF_CORE_TYPES 5

namespace lib4aio {

    template<typename T>
    class array_list;

    class str_hook;
}

struct aio_file;

class aio_bundle;

using namespace lib4aio;

class aio_core {

    friend class aio_core_builder;

public:

    static aio_core *create();

    aio_core *configure();

    aio_core *inflate(char *build_path);

    aio_core *invoke(int argc, char *const *argv);

    void finish();

    array_list<str_hook> *get_types() const;

    array_list<aio_file> *get_files() const;

private:

    array_list<str_hook> *types;

    array_list<aio_file> *files;

    explicit aio_core();
};

#endif //AIO_CORE_H