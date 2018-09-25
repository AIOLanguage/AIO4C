#include <cstring>
#include <cstdlib>
#include <aio_core/aio_core.h>
#include <aio_parsing/aio_context_inflater/aio_context_inflater.h>
#include <aio_runtime/aio_runtime.h>
#include <aio_runtime/aio_build_runtime.h>
#include <lib4aio_cpp_headers/aio_orbit/aio_orbit.h>
#include <lib4aio_cpp_sources/aio_orbit/aio_orbit.cpp>
#include <lib4aio_cpp_headers/utils/file_utils/file_reader.h>
#include <lib4aio_cpp_headers/utils/str_builder/str_builder.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/string_utils/suffix_prefix.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>
#include <lib4aio_cpp_headers/utils/pair/aio_pair.h>
#include <lib4aio_cpp_headers/utils/char_utils/char_utils.h>
#include <aio_parsing/aio_orbits/aio_file/aio_file_orbit.h>
#include <aio_runtime/aio_variable/aio_variable.h>
#include <aio_lang/aio_space/aio_file/aio_file.h>
#include <aio_runtime/aio_ray/aio_ray.h>
#include <aio_lang/aio_field/aio_field.h>
#include <aio_lang/aio_types/aio_types.h>
#include <lib4aio_cpp_headers/aio_path_util/aio_path_util.h>
#include <aio_runtime/aio_value/advanced_functions/cast_aio_value.h>
#include <aio_runtime/aio_value/aio_value.h>
#include <lib4aio_cpp_headers/utils/string_utils/common.h>
#include <aio_runtime/aio_program_runtime.h>


#define AIO_INFLATTER_DEBUG

#define AIO_INFLATTER_ERROR_TAG "AIO_INFLATTER_ERROR"

#define AIO_INFLATTER_INFO_TAG "AIO_INFLATTER_INFO"

#ifdef AIO_INFLATTER_DEBUG

#endif

/**
 * 비즈니스 로직.
 */

#define AIO_BUILD_SCRIPT_FORMAT ".aio_core"

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
    const bool is_aio_build_script_file = ends_with_suffix(this->script_path, AIO_BUILD_SCRIPT_FORMAT);
    if (is_aio_build_script_file) {
        aio_runtime *build_runtime = reinterpret_cast<aio_runtime *>(this->core->build_runtime);
        inflate_aio_file(this->script_path, build_runtime);
    } else {
        throw_error_with_details(AIO_INFLATTER_ERROR_TAG, "파일이 '*.aio_core' 형식이 아닙니다", this->script_path);
    }
}

void aio_context_inflater::invoke_aio_build_script()
{
    //Get build build_runtime:
    aio_build_runtime *build_runtime = this->core->build_runtime;
    //Get script:
    const aio_file *build_script = build_runtime->get_file_list()->last();
    //Get script instructions:
    const aio_scheme *script_scheme = build_script->get_scheme();
    //Make build script runtime by instructions:
    this->build_ray = aio_ray::new_aio_ray(script_scheme)->perform();
    //Get global properties from script runtime and don't close build runtime:
    array_list<aio_variable> *script_properties = this->build_ray->get_variables();
    //Set main:
    build_runtime->main = script_properties->find_by(
            [](const aio_variable *it) -> bool {
                return it->get_definition()->type->equals_string(AIOMAIN_TYPE);
            });
    //Set processors;
    build_runtime->processors = script_properties->collect_by(
            [](aio_variable *it) -> bool {
                return it->get_definition()->type->equals_string(AIOPROCESSOR_TYPE);
            });
}

void aio_context_inflater::inflate_aio_program()
{
    aio_program_runtime *program_runtime = this->core->program_runtime;
    //Get main property value from build script runtime:
    aio_build_runtime *build_runtime = this->core->build_runtime;
    aio_variable *main_property = build_runtime->get_main_property();
    aio_value *relative_main_path = cast_to_string(main_property->get_value());
    const char *string = relative_main_path->get.string_acc;
    char *absolute_main_path = construct_absolute_path(string, this->script_path);
    this->inflate_aio_file(absolute_main_path, program_runtime);
    //Save main path in core:
    program_runtime->set_entry_path(new_string(string));
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기:
    free(absolute_main_path);
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
                const str_hook *path = file->get_relative_path();
                const bool already_has_the_same_path = path->equals_string(relative_file_path);
                return already_has_the_same_path;
            }
    );
    if (!has_same_file) {
        char *absolute_path = construct_absolute_path(relative_file_path, script_path);
        inflate_aio_file(absolute_path, runtime);
    }
}

void aio_context_inflater::inflate_aio_file(const char *root_path, aio_runtime *runtime)
{
    str_builder *content = read_file_by_str_builder(root_path);
    const unsigned content_length = content->size();
    const bool has_content = content_length > 0;
    if (has_content) {
        const char *content_string = content->get_string();
        const str_hook *holder = new str_hook(content_string, 0, content_length);
        //Create build file orbit:
        array_list<aio_file> *file_list = runtime->get_file_list();
        aio_orbit<aio_file> *file_orbit = new aio_file_orbit(file_list, content);
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

void aio_context_inflater::destroy()
{
    delete this;
}