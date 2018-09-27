#ifndef AIO_CLASS_ORBIT_H
#define AIO_CLASS_ORBIT_H

#include <lib4aio_cpp_headers/aio_orbit/aio_orbit.h>

using namespace lib4aio;

class aio_class;

class aio_runtime;

class aio_class_orbit : public aio_orbit<aio_class> {

public:

    explicit aio_class_orbit(aio_class *class_ptr, aio_runtime *runtime_ptr);

    ~aio_class_orbit();
};

#endif //AIO_CLASS_ORBIT_H