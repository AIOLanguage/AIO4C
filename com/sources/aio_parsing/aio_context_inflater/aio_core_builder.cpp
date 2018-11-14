//native:
#include <cstdlib>
//core:
#include <aio_core/aio_core.h>
//lang:
#include <aio_lang/aio_types/aio_types.h>
#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_space/aio_file/aio_file.h>
//parsing:
#include <aio_parsing/aio_core_builder/aio_core_builder.h>
//particles:
#include <aio_parsing/aio_particles/aio_class/aio_class_particle.h>
#include <aio_parsing/aio_particles/aio_field/aio_field_particle.h>
#include <aio_parsing/aio_particles/aio_scope/aio_scope_particle.h>
#include <aio_parsing/aio_particles/aio_import/aio_import_particle.h>
#include <aio_parsing/aio_particles/aio_function/aio_function_particle.h>
//runtime:
#include <aio_runtime/aio_ray/aio_ray.h>
//#include <aio_runtime/aio_ray/aio_ray.cpp>
#include <aio_runtime/aio_variable/aio_variable.h>
#include <aio_runtime/aio_value/advanced_functions/cast_aio_value.h>
//lib4aio:
#include <lib4aio_cpp_headers/aio_orbit/aio_orbit.h>
#include <lib4aio_cpp_sources/aio_orbit/aio_orbit.cpp>
#include <lib4aio_cpp_headers/utils/string_utils/common.h>
#include <lib4aio_cpp_headers/aio_path_util/aio_path_util.h>
#include <lib4aio_cpp_headers/utils/file_utils/file_reader.h>
#include <lib4aio_cpp_headers/utils/str_builder/str_builder.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/string_utils/suffix_prefix.h>
#include <lib4aio_cpp_headers/utils/array_list_utils/array_list.h>
#include <lib4aio_cpp_sources/utils/array_list_utils/array_list.cpp>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

/**
 * 태그들.
 */

#define AIO_CORE_BUILDER_DEBUG

#define AIO_CORE_BUILDER_ERROR_TAG "AIO_CORE_BUILDER_ERROR"

#define AIO_CORE_BUILDER_WARNING_TAG "AIO_CORE_BUILDER_WARNING"

#define AIO_CORE_BUILDER_INFO_TAG "AIO_CORE_BUILDER_INFO"

#ifdef AIO_CORE_BUILDER_DEBUG

//lib4aio:
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>

#endif

/**
 * 비즈니스 로직.
 */

#define AIO_FORMAT ".aio"

using namespace lib4aio;

aio_core_builder *aio_core_builder::create()
{
    return new aio_core_builder();
}

aio_core_builder *aio_core_builder::set_core(aio_core *core)
{
    this->core_ptr = core;
    //------------------------------------------------------------------------------------------------------------------
    return this;
}

aio_core_builder *aio_core_builder::set_build_path(char *build_path)
{
    this->build_path = build_path;
    //------------------------------------------------------------------------------------------------------------------
    return this;
}


aio_core_builder *aio_core_builder::construct()
{
    this->grub_aio_files();
    this->construct_aio_files();
    //------------------------------------------------------------------------------------------------------------------
    return this;
}

void aio_core_builder::grub_aio_file(const char *path)
{
    str_builder *content = read_file_by_str_builder(path);
#ifdef AIO_CORE_BUILDER_DEBUG
    log_info_string(AIO_CORE_BUILDER_INFO_TAG, "File content:\n\n\n", content->get_string());
#endif
    const unsigned content_length = content->size();
    const bool has_content = content_length > 0;
    if (has_content) {
        //Create new aio file:
        const char *copy_of_path = new_string(path);
        aio_file *file = new aio_file(content, copy_of_path);
        //Parse file and fill aio file:
        aio_orbit<aio_schemable>::create()
                ->set_pivot(file)
                ->set_radius(new str_hook(content->get_string(), 0, content_length))
//                ->set_particle(new aio_field_particle())
                ->spin();
#ifdef AIO_CORE_BUILDER_DEBUG
        log_info(AIO_CORE_BUILDER_INFO_TAG, "File inflating is complete");
#endif
        this->core_ptr->files->add(file);
    }
}

void aio_core_builder::finish()
{}

void aio_core_builder::grub_aio_files()
{

}

void aio_core_builder::construct_aio_files()
{

}

//
//static array_list<aio_particle<aio_file>> *new_file_particle_list(aio_runtime *runtime, aio_file *file)
//{
//    array_list<str_hook> *type_list = runtime->get_types();
//    //Create particles:
////    aio_class_particle<aio_file> *typename_particle = new aio_class_particle<aio_file>(runtime, file->typenames);
//    aio_field_particle<aio_file> *field_particle = new aio_field_particle<aio_file>(type_list, file->fields.txt, false);
////    aio_scope_particle<aio_file> *scope_particle = new aio_scope_particle<aio_file>(runtime, file->pathnames);
//    aio_function_particle<aio_file> *function_particle = new aio_function_particle<aio_file>(runtime, file->functions);
////    aio_import_particle<aio_file> *import_particle = new aio_import_particle<aio_file>(runtime->get_file_list());
//    //Add particles:
//    array_list<aio_particle<aio_file>> *particle_list = new array_list<aio_particle<aio_file>>();
//    particle_list->add(field_particle);
////    particle_list->add(scope_particle);
////    particle_list->add(import_particle);
////    particle_list->add(function_particle);
////    particle_list->add(typename_particle);
//    //aio_filemode<>...
//#ifdef AIO_FILE_ORBIT_DEBUG
//    log_info_int(AIO_FILE_ORBIT_INFO_TAG, "Created file particles, count:", particle_list->get_size());
//#endif
//    return particle_list;
//}