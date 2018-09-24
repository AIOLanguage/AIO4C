#include <cstdlib>
#include <aio_core/aio_core.h>
#include <aio_core/aio_build_script.h>
#include <aio_parsing/aio_context_inflater/aio_context_inflater.h>
#include <aio_parsing/aio_orbits/aio_build_script/aio_build_script_orbit.h>
#include <aio_runtime/aio_runtime.h>
#include <lib4aio_cpp_headers/aio_orbit/aio_orbit.h>
#include <lib4aio_cpp_sources/aio_orbit/aio_orbit.cpp>
#include <lib4aio_cpp_headers/utils/file_utils/file_reader.h>
#include <lib4aio_cpp_headers/utils/str_builder/str_builder.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/string_utils/suffix_prefix.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>
#include <lib4aio_cpp_headers/utils/pair/aio_pair.h>
#include <cstring>
#include <lib4aio_cpp_headers/utils/char_utils/char_utils.h>
#include <aio_parsing/aio_orbits/aio_file/aio_file_orbit.h>
#include <aio_lang/aio_space/aio_file/aio_file.h>
#include <aio_runtime/aio_ray/aio_ray.h>


#define AIO_INFLATTER_DEBUG

#define AIO_INFLATTER_ERROR_TAG "AIO_INFLATTER_ERROR"

#define AIO_INFLATTER_INFO_TAG "AIO_INFLATTER_INFO"

#ifdef AIO_INFLATTER_DEBUG

#endif

/**
 * 비즈니스 로직.
 */

#define AIO_BUILD_SCRIPT_FORMAT ".aio_core"

#define AIO_SUFFIX ".aio"

using namespace lib4aio;

aio_context_inflater::aio_context_inflater(aio_core *core, const char *script_path)
{
    this->core = core;
    this->script_path = script_path;
}

aio_context_inflater::~aio_context_inflater()
{}

void aio_context_inflater::inflate()
{
    this->inflate_aio_build_script();
    this->invoke_aio_build_script();
    this->inflate_aio_files();
}

void aio_context_inflater::inflate_aio_build_script()
{
    const bool is_aio_build_script_file = ends_with_suffix(this->script_path, AIO_BUILD_SCRIPT_FORMAT);
    if (is_aio_build_script_file) {
        str_builder *script_content = read_file_by_str_builder(this->script_path);
        const unsigned script_content_length = script_content->size();
        const bool has_content = script_content_length > 0;
        if (has_content) {
            const char *build_script_content = script_content->get_string();
            const str_hook *build_script_holder = new str_hook(build_script_content, 0, script_content_length);
            //Create build script orbit:
            aio_orbit<aio_build_script> *script_orbit = new aio_build_script_orbit(script_content);
            aio_build_script *script = script_orbit->make(build_script_holder);
            //Add script:
            this->core->build_runtime->get_file_list()->add(script);
            //----------------------------------------------------------------------------------------------------------
            //찌꺼기 수집기:
            delete build_script_holder;
            delete script_orbit;
            //----------------------------------------------------------------------------------------------------------
        } else {
            throw_error_with_tag(AIO_INFLATTER_ERROR_TAG, "파일 내용 비어있습니다");
        }
    } else {
        throw_error_with_details(AIO_INFLATTER_ERROR_TAG, "파일이 '*.aio_core' 형식이 아닙니다", this->script_path);
    }
}


void aio_context_inflater::invoke_aio_build_script()
{
    const aio_file *build_script = this->core->build_runtime->get_file_list()->last();
    const aio_scheme *script_scheme = build_script->get_scheme();
    //Make build script runtime:
    aio_ray *ray = new aio_ray(script_scheme);
    ray->perform();
    const array_list<aio_variable> *script_properties = ray->get_variables();
    //Put main;
    //Put processors;
}

void aio_context_inflater::inflate_aio_files()
{
    const char *relative_main_path = this->core->build_runtime->get_main_property_value();
    const str_hook *path_holder = new str_hook(relative_main_path);
    this->inflate_aio_file(path_holder, this->script_path, this->core->program_runtime);
}

#define SLASH_SYMBOL '/'

static char *construct_absolute_path(const str_hook *relative_path, const char *script_path)
{
    const char *source_file_path_string = relative_path->get_string();
    str_builder *sb = new str_builder();
    sb->append(script_path);
    sb->append(SLASH_SYMBOL);
    for (unsigned i = relative_path->start; i < relative_path->end; ++i) {
        const char symbol = source_file_path_string[i];
        if (is_dot(symbol)) {
            sb->append(SLASH_SYMBOL);
        } else {
            sb->append(symbol);
        }
    }
    char *absolute_path = sb->pop();
    //------------------------------------------------------------------------------------------------------------------
    //찌꺼기 수집기:
    delete sb;
    //------------------------------------------------------------------------------------------------------------------
    return absolute_path;
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
        str_builder *file_content = read_file_by_str_builder(absolute_path);
        str_hook *file_content_holder = new str_hook(file_content->get_string(), 0, file_content->size());
        //Create file orbit:
        aio_orbit<aio_file> *file_orbit = new aio_file_orbit(file_list, file_content);
        aio_file *file = file_orbit->make(file_content_holder);
        file_list->add(file);
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼끼 수집기:
        delete file_orbit;
        delete file_content_holder;
        free(absolute_path);
    }
}
