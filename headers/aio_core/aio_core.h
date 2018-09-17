#ifndef AIO_CORE_H
#define AIO_CORE_H

/**
 * 연결.
 */

#define NUMBER_OF_CORE_TYPES 5

namespace lib4aio {

    template <class T> class array_list;

    class str_hook;
}

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

    array_list<str_hook> *types;

    array_list<aio_file> *file_list;

    aio_core();

    ~aio_core();
};

#endif //AIO_CORE_H