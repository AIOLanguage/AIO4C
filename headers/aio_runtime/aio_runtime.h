#ifndef AIO_RUNTIME_H
#define AIO_RUNTIME_H

namespace lib4aio {

    template<typename T>
    class array_list;

    class str_hook;
}

class aio_ray;

using namespace lib4aio;

class aio_file;

class aio_runtime {

public:

    aio_runtime(const bool has_access);

    ~aio_runtime();

    array_list<str_hook> *get_types() const;

    array_list<aio_file> *get_file_list() const;

private:

    bool has_access;

    array_list<str_hook> *types;

    array_list<aio_file> *file_list;
};
#endif //AIO_RUNTIME_H