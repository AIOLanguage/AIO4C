#ifndef AIO_CORE_H
#define AIO_CORE_H

/**
 * 연결.
 */

#include <lib4aio_cpp_headers/utils/str_builder/str_builder.h>

#define NUMBER_OF_CORE_TYPES 5

namespace lib4aio {

    template<class T>
    class array_list;

    class str_hook;

    class str_builder;
}

using namespace lib4aio;

class aio_file;

/**
 * 글로벌 핵심.
 */

class aio_core {

public:

    static void inflate(const int argc, char **argv);

    const array_list<str_hook> *get_types() const;

    const array_list<aio_file> *get_file_list() const;

    void set_script_builder(str_builder *script_builder);

private:

    str_builder *script_builder;

    array_list<str_hook> *types;

    array_list<aio_file> *file_list;

    aio_core();

    ~aio_core();
};

#endif //AIO_CORE_H