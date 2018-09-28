//lang:
#include <aio_lang/aio_space/aio_scope/aio_scope.h>
//parsing:
#include <aio_parsing/aio_orbits/aio_scope/aio_scope_orbit.h>
#include <aio_parsing/aio_particles/aio_class/aio_class_particle.h>
#include <aio_parsing/aio_particles/aio_class/aio_class_particle.cpp>
#include <aio_parsing/aio_particles/aio_field/aio_field_particle.h>
#include <aio_parsing/aio_particles/aio_field/aio_field_particle.cpp>
#include <aio_parsing/aio_particles/aio_scope/aio_scope_particle.h>
#include <aio_parsing/aio_particles/aio_scope/aio_scope_particle.cpp>
#include <aio_parsing/aio_particles/aio_function/aio_function_particle.h>
#include <aio_parsing/aio_particles/aio_function/aio_function_particle.cpp>
//runtime:
#include <aio_runtime/aio_runtime.h>
//lib4aio:
#include <lib4aio_cpp_sources/aio_orbit/aio_orbit.cpp>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>

static array_list<aio_particle<aio_scope>> *new_scope_particle_list(aio_runtime *runtime_ptr, aio_scope *scope_ptr)
{
    array_list<aio_particle<aio_scope>> *particle_list = new array_list<aio_particle<aio_scope>>();
    particle_list->add(new aio_class_particle<aio_scope>(runtime_ptr, scope_ptr->class_definition_list));
    particle_list->add(new aio_field_particle<aio_scope>(runtime_ptr->get_types(), scope_ptr->field_definition_list));
    particle_list->add(new aio_scope_particle<aio_scope>(runtime_ptr, scope_ptr->scope_definition_list));
    particle_list->add(new aio_function_particle<aio_scope>(runtime_ptr, scope_ptr->function_definition_list));
    return particle_list;
}

aio_scope_orbit::aio_scope_orbit(aio_scope *scope_ptr, aio_runtime *runtime_ptr)
{
    this->container_ptr = scope_ptr;
    this->particle_list = new_scope_particle_list(runtime_ptr, scope_ptr);
}

aio_scope_orbit::~aio_scope_orbit()
{}