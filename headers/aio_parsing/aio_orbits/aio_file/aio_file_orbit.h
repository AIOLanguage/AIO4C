#ifndef AIO_FILE_ORBIT_H
#define AIO_FILE_ORBIT_H

#include <lib4aio_cpp_headers/aio_orbit/aio_orbit.h>

namespace lib4aio {

    template<typename T>
    class array_list;

    class str_builder;
}

using namespace lib4aio;

class aio_file;

class aio_file_orbit : public aio_orbit<aio_file> {

public:

    aio_file_orbit(array_list<aio_file> *file_collection, str_builder *file_content);

    ~aio_file_orbit();
};

#endif //AIO_FILE_ORBIT_H
