#include <aio_core/aio_build_script.h>
#include <aio_parsing/aio_orbits/aio_build_script/aio_build_script_orbit.h>
#include <aio_parsing/aio_orbits/aio_build_script/aio_particles/aio_build_script_attribute_particle.h>
#include <lib4aio_cpp_sources/aio_orbit/aio_orbit.cpp>
#include <lib4aio_cpp_headers/utils/memory_utils/memory_utils.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>

#define AIO_BUILD_SCRIPT_ORBIT_DEBUG

#define AIO_BUILD_SCRIPT_ORBIT_INFO_TAG "AIO_BUILD_SCRIPT_ORBIT_INFO"

#ifdef AIO_BUILD_SCRIPT_ORBIT_DEBUG

#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>

#endif

using namespace lib4aio;

static array_list<aio_particle<aio_build_script>> *new_particle_list()
{
    array_list<aio_particle<aio_build_script>> *list = new array_list<aio_particle<aio_build_script>>();
    aio_build_script_attribute_particle *attribute_particle = new aio_build_script_attribute_particle();
    list->add(attribute_particle);
    return list;
}

aio_build_script_orbit::aio_build_script_orbit(str_builder *script_content) : aio_orbit(
        new_particle_list(),
        [&script_content]() -> aio_build_script * {
            return new aio_build_script(script_content);
        })
{}

aio_build_script_orbit::~aio_build_script_orbit()
{}