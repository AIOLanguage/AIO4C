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

typedef enum aio_runtime_type {
    AIO_RUNTIME_TYPE_BUILD, AIO_RUNTIME_TYPE_PROGRAM
} aio_runtime_type;

class aio_runtime {

public:

    explicit aio_runtime(const aio_runtime_type type);

    virtual ~aio_runtime();

    array_list<str_hook> *get_types() const;

    array_list<aio_file> *get_file_list() const;

    const aio_runtime_type get_runtime_type() const ;

private:

    aio_runtime_type runtime_type;

    array_list<str_hook> *types;

    array_list<aio_file> *file_list;
};

#endif //AIO_RUNTIME_H