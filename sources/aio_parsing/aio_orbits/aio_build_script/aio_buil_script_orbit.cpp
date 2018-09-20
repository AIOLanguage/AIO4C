#include <aio_parsing/aio_orbits/aio_build_script/aio_build_script_orbit.h>
#include <lib4aio_cpp_headers/utils/memory_utils/memory_utils.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>

using namespace lib4aio;

aio_build_script_space *aio_build_script_orbit::new_space()
{
    aio_build_script_space *build_script_space = (aio_build_script_space *) new_object(sizeof(aio_build_script_space));
    return build_script_space;
}

array_list<aio_particle<aio_build_script_space>> *aio_build_script_orbit::create_particle_list()
{
    array_list<aio_particle<aio_build_script_space>> *list = new array_list<aio_particle<aio_build_script_space>>();
    return list;
}