//native:
#include <cstdlib>
//core:
#include <aio_core/aio_core.h>
//lang:
#include <aio_lang/aio_types/aio_types.h>
#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_space/aio_file/aio_file.h>
//parsing:
#include <aio_runtime/aio_value/aio_value.h>
#include <aio_parsing/aio_orbits/aio_file/aio_file_orbit.h>
#include <aio_parsing/aio_context_inflater/aio_context_inflater.h>
//runtime:
#include <aio_runtime/aio_ray/aio_ray.h>
#include <aio_runtime/aio_ray/aio_ray.cpp>
#include <aio_runtime/aio_build_runtime.h>
#include <aio_runtime/aio_program_runtime.h>
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

#define AIO_INFLATTER_DEBUG

#define AIO_INFLATTER_ERROR_TAG "AIO_INFLATTER_ERROR"

#define AIO_INFLATTER_INFO_TAG "AIO_INFLATTER_INFO"

#ifdef AIO_INFLATTER_DEBUG

//lib4aio:
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>

#endif

/**
 * 비즈니스 로직.
 */

#define AIO_FORMAT ".aio"

using namespace lib4aio;

aio_context_inflater *aio_context_inflater::create()
{
    return new aio_context_inflater();
}

aio_context_inflater *aio_context_inflater::set_core(aio_core *core)
{
    this->core = core;
    //------------------------------------------------------------------------------------------------------------------
    return this;
}

aio_context_inflater *aio_context_inflater::set_script_path(const char *script_path)
{
    this->script_path = script_path;
    //------------------------------------------------------------------------------------------------------------------
    return this;
}

aio_context_inflater *aio_context_inflater::inflate()
{
    this->inflate_aio_build_script();
    this->invoke_aio_build_script();
    this->inflate_aio_program();
    //------------------------------------------------------------------------------------------------------------------
    return this;
}

void aio_context_inflater::inflate_aio_build_script()
{
    aio_runtime *runtime = this->core->build_runtime;
    const str_hook *empty_relative_path = new str_hook();
    this->inflate_aio_file(empty_relative_path, this->script_path, runtime);
    //--------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기:
    delete empty_relative_path;
}

void aio_context_inflater::invoke_aio_build_script()
{
    //Get build build_runtime:
    aio_build_runtime *build_runtime = this->core->build_runtime;
    //Get script:
    const aio_file *build_script = build_runtime->get_file_list()->last();
    //Make build script runtime by instructions:
    aio_ray<aio_file> *build_ray = new aio_ray<aio_file>();
    build_ray->perform(build_script);
    //Get global properties from script runtime and don't close build runtime:
    array_list<aio_variable> *script_properties = build_ray->get_variables();
    //Set build build_ray:
    build_runtime->build_ray_ptr = build_ray;
    //Set main:
    build_runtime->main_ptr = script_properties->find_by(
            [](aio_variable *it) -> bool {
                return it->get_definition()->type->equals_string(AIOMAIN_TYPE);
            });
    //Set processors;
    build_runtime->processors_ptr = script_properties->collect_by(
            [](aio_variable *it) -> bool {
                return it->get_definition()->type->equals_string(AIOPROCESSOR_TYPE);
            });
}

void aio_context_inflater::inflate_aio_program()
{
    aio_program_runtime *program_runtime = this->core->program_runtime;
    //Get main property value from build script runtime:
    aio_build_runtime *build_runtime = this->core->build_runtime;
    aio_variable *main_property = build_runtime->get_main_property_ptr();
    aio_value *relative_main_path = cast_to_string(main_property->get_value());
    char *copy_of_path = new_string(relative_main_path->get.string_acc);
    str_hook *path_holder = new str_hook(copy_of_path);
    //Save main path in core:
    program_runtime->set_entry_path(copy_of_path);
    this->inflate_aio_file(path_holder, this->script_path, program_runtime);
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기:
    delete path_holder;
    free_aio_value(relative_main_path);
}

void aio_context_inflater::inflate_aio_file(
        const str_hook *relative_file_path,
        const char *script_path,
        aio_runtime *runtime
)
{
    array_list<aio_file> *file_list = runtime->get_file_list();
    const bool has_same_file = file_list->contains_by(
            [&relative_file_path](const aio_file *file) -> bool {
                const str_hook *path = file->relative_path;
                const bool already_has_the_same_path = path->equals_string(relative_file_path);
                return already_has_the_same_path;
            }
    );
    if (!has_same_file) {
        char *absolute_path = construct_absolute_path(relative_file_path, script_path);
        str_builder *content = read_file_by_str_builder(absolute_path);
#ifdef AIO_INFLATTER_DEBUG
        log_info_string(AIO_INFLATTER_INFO_TAG, "File content:", content->get_string());
        exit(8);
#endif
        const unsigned content_length = content->size();
        const bool has_content = content_length > 0;
        if (has_content) {
            const char *content_string = content->get_string();
            const str_hook *holder = new str_hook(content_string, 0, content_length);
            //Create build file orbit:
            aio_orbit<aio_file> *file_orbit = new aio_file_orbit(runtime, content, relative_file_path);
            aio_file *file = file_orbit->make(holder);
            //Add file:
            file_list->add(file);
            //----------------------------------------------------------------------------------------------------------
            //찌꺼기 수집기:
            delete holder;
            delete file_orbit;
            //----------------------------------------------------------------------------------------------------------
        } else {
            throw_error_with_tag(AIO_INFLATTER_ERROR_TAG, "파일 내용 비어있습니다");
        }
    }
}

void aio_context_inflater::destroy()
{
    delete this;
}