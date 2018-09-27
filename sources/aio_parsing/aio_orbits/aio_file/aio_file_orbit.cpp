//lang:
#include <aio_lang/aio_space/aio_file/aio_file.h>
//parsing:
#include <aio_parsing/aio_orbits/aio_file/aio_file_orbit.h>
#include <aio_parsing/aio_particles/aio_class/aio_class_particle.h>
#include <aio_parsing/aio_particles/aio_field/aio_field_particle.h>
#include <aio_parsing/aio_particles/aio_scope/aio_scope_particle.h>
#include <aio_parsing/aio_particles/aio_import/aio_import_particle.h>
#include <aio_parsing/aio_particles/aio_function/aio_function_particle.h>
//lib4aio:
#include <lib4aio_cpp_headers/aio_orbit/aio_orbit.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_headers/aio_orbit/aio_particle/aio_particle.h>

using namespace lib4aio;

static array_list<aio_particle<aio_file>> *new_file_particle_list(aio_runtime *runtime)
{
    array_list<aio_particle<aio_file>> *particle_list = new array_list<aio_particle<aio_file>>();
    particle_list->add(new aio_class_particle<aio_file>());
    particle_list->add(new aio_field_particle<aio_file>(runtime->get_runtime_type()));
    particle_list->add(new aio_scope_particle<aio_file>());
    particle_list->add(new aio_function_particle<aio_file>());
    particle_list->add(new aio_import_particle<aio_file>(runtime->get_file_list()));
    return particle_list;
}

aio_file_orbit::aio_file_orbit(aio_runtime *runtime, str_builder *file_content)
        : aio_orbit(new_file_particle_list(runtime),
                [&file_content]() -> aio_file * {
                        aio_file *file = new aio_file();
                        file->set_content(file_content);
                        return file;
                    }
)
{}

aio_file_orbit::~aio_file_orbit()
{}