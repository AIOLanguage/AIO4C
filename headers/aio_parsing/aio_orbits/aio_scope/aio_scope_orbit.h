#ifndef AIO_SCOPE_ORBIT_H
#define AIO_SCOPE_ORBIT_H

#include <lib4aio_cpp_headers/aio_orbit/aio_orbit.h>

using namespace lib4aio;

class aio_scope;

class aio_runtime;

class aio_scope_orbit : public aio_orbit<aio_scope> {

public:

    explicit aio_scope_orbit(aio_scope *scope_ptr, aio_runtime *runtime_ptr);

    ~aio_scope_orbit();
};

#endif //AIO_SCOPE_ORBIT_H