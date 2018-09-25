#ifndef AIO_BUILD_RUNTIME_H
#define AIO_BUILD_RUNTIME_H

#include <aio_runtime/aio_runtime.h>


namespace lib4aio {

    template<typename T>
    class array_list;
}

class aio_variable;

class aio_build_runtime : public aio_runtime {

    friend class aio_context_inflater;

public:

    explicit aio_build_runtime();

    ~aio_build_runtime();

    aio_variable *get_main_property() const;

    array_list<aio_variable> *get_processors() const;

private:

    const aio_variable *main;

    array_list<aio_variable> *processors;
};

#endif //AIO_BUILD_RUNTIME_H
