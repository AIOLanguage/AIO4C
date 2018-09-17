#ifndef AIO_CORE_H
#define AIO_CORE_H

/**
 * 연결.
 */

 #include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook_list/str_hook_list.h>

#define NUMBER_OF_CORE_TYPES 5

using namespace lib4aio;

class aio_file;

class aio_core {

public:

    static void inflate_aio_core(const int argc, char *argv[]);

    static aio_core *get_instance();

    const array_list<str_hook> *get_types() const;

    const array_list<aio_file> *get_file_list() const;

    aio_core(aio_core const & rhs) = delete;

    aio_core& operator=(aio_core const & rhs) = delete;

private:

    /**
     * 글로벌 핵심.
     */

    static aio_core *core;

    array_list<str_hook> *types;

    array_list<aio_file> *file_list;

    aio_core();

    ~aio_core();
};

#endif //AIO_CORE_H