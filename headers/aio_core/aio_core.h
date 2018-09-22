#ifndef AIO_CORE_H
#define AIO_CORE_H

#define NUMBER_OF_CORE_TYPES 5

namespace lib4aio {

    template<class T>
    class array_list;

    class str_hook;
}

using namespace lib4aio;

class aio_file;

class aio_build_script_space;

/**
 * 글로벌 핵심.
 */

class aio_core {

public:

    static void inflate(const int argc, char **argv);

    const array_list<str_hook> *get_types() const;

    const array_list<aio_file> *get_file_list() const;

    void set_aio_file_list(array_list<aio_file> *files);

    void set_build_script_materials(const aio_build_script_space *script_materials);

private:

    const aio_build_script_space *build_script_materials;

    array_list<str_hook> *types;

    array_list<aio_file> *file_list;

    aio_core();

    ~aio_core();
};

#endif //AIO_CORE_H