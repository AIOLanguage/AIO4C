//lang:
#include <aio_lang/aio_space/aio_initializable/aio_class/aio_class.h>
//parsing:
#include <aio_parsing/aio_orbits/aio_class/aio_class_orbit.h>
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
#include <aio_parsing/aio_particles/aio_constructor/aio_constructor_particle.h>
#include <aio_parsing/aio_particles/aio_constructor/aio_constructor_particle.cpp>
//runtime:
#include <aio_runtime/aio_runtime.h>
//lib4aio:
#include <lib4aio_cpp_sources/aio_orbit/aio_orbit.cpp>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>

static array_list<aio_particle<aio_class>> *new_class_particle_list(aio_runtime *runtime_ptr, aio_class *class_ptr)
{
    array_list<aio_particle<aio_class>> *particle_list = new array_list<aio_particle<aio_class>>();
    particle_list->add(new aio_class_particle<aio_class>(runtime_ptr, class_ptr->typenames));
//    particle_list->add(new aio_field_particle<aio_class>(runtime_ptr->get_types(), class_ptr->fields));
    particle_list->add(new aio_scope_particle<aio_class>(runtime_ptr, class_ptr->pathnames));
    particle_list->add(new aio_function_particle<aio_class>(runtime_ptr, class_ptr->functions));
    particle_list->add(new aio_constructor_particle<aio_class>(runtime_ptr, class_ptr->constructor_definition_list));
    return particle_list;
}

aio_class_orbit::aio_class_orbit(aio_class *class_ptr, aio_runtime *runtime_ptr)
{
    this->container_ptr = class_ptr;
    this->particle_list = new_class_particle_list(runtime_ptr, class_ptr);
}

aio_class_orbit::~aio_class_orbit()
{}