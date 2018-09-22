#ifndef AIO_BUILD_SCRIPT_ORBIT_H
#define AIO_BUILD_SCRIPT_ORBIT_H

#include <lib4aio_cpp_headers/aio_orbit/aio_orbit.h>

using namespace lib4aio;

class aio_build_script_space;

class aio_build_script_orbit : public aio_orbit<aio_build_script_space> {

public:

    aio_build_script_orbit();
};

#endif //AIO_BUILD_SCRIPT_ORBIT_H