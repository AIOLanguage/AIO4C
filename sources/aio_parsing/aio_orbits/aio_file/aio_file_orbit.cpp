//lang:
#include <aio_lang/aio_space/aio_file/aio_file.h>
//parsing:
#include <aio_parsing/aio_orbits/aio_file/aio_file_orbit.h>
#include <aio_parsing/aio_particles/aio_class/aio_class_particle.h>
#include <aio_parsing/aio_particles/aio_class/aio_class_particle.cpp>
#include <aio_parsing/aio_particles/aio_field/aio_field_particle.h>
#include <aio_parsing/aio_particles/aio_field/aio_field_particle.cpp>
#include <aio_parsing/aio_particles/aio_scope/aio_scope_particle.h>
#include <aio_parsing/aio_particles/aio_scope/aio_scope_particle.cpp>
#include <aio_parsing/aio_particles/aio_import/aio_import_particle.h>
#include <aio_parsing/aio_particles/aio_import/aio_import_particle.cpp>
#include <aio_parsing/aio_particles/aio_function/aio_function_particle.h>
#include <aio_parsing/aio_particles/aio_function/aio_function_particle.cpp>
//runtime:
#include <aio_runtime/aio_runtime.h>
//lib4aio:
#include <lib4aio_cpp_headers/aio_orbit/aio_orbit.h>
#include <lib4aio_cpp_sources/aio_orbit/aio_orbit.cpp>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>
#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

using namespace lib4aio;

#define AIO_FILE_ORBIT_INFO_TAG "AIO_FILE_ORBIT_INFO"

#define AIO_FILE_ORBIT_DEBUG

#ifdef AIO_FILE_ORBIT_DEBUG

#endif

static array_list<aio_particle<aio_file>> *new_file_particle_list(aio_runtime *runtime, aio_file *file)
{
    array_list<str_hook> *type_list = runtime->get_types();
    //Create particles:
//    aio_class_particle<aio_file> *typename_particle = new aio_class_particle<aio_file>(runtime, file->typenames);
    aio_field_particle<aio_file> *field_particle = new aio_field_particle<aio_file>(type_list, file->fields, false);
//    aio_scope_particle<aio_file> *scope_particle = new aio_scope_particle<aio_file>(runtime, file->pathnames);
    aio_function_particle<aio_file> *function_particle = new aio_function_particle<aio_file>(runtime, file->functions);
//    aio_import_particle<aio_file> *import_particle = new aio_import_particle<aio_file>(runtime->get_file_list());
    //Add particles:
    array_list<aio_particle<aio_file>> *particle_list = new array_list<aio_particle<aio_file>>();
    particle_list->add(field_particle);
//    particle_list->add(scope_particle);
//    particle_list->add(import_particle);
//    particle_list->add(function_particle);
//    particle_list->add(typename_particle);
    //aio_filemode<>...
#ifdef AIO_FILE_ORBIT_DEBUG
    log_info_int(AIO_FILE_ORBIT_INFO_TAG, "Created file particles, count:", particle_list->get_size());
#endif
    return particle_list;
}

aio_file_orbit::aio_file_orbit(
        aio_runtime *runtime,
        str_builder *file_content,
        const str_hook *relative_file_path
)
{
    aio_file *file = new aio_file(file_content, relative_file_path);
    this->container_ptr = file;
    this->particle_list = new_file_particle_list(runtime, file);
}

aio_file_orbit::~aio_file_orbit()
{}