#include <aio_core/aio_core.h>
#include <aio_parsing/aio_orbits/aio_build_script/aio_build_script_orbit.h>
#include <lib4aio_cpp_sources/aio_orbit/aio_orbit.cpp>
#include <lib4aio_cpp_headers/utils/file_utils/file_reader.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/string_utils/suffix_prefix.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

#define AIO_INFLATTER_DEBUG

#define AIO_INFLATTER_ERROR_TAG "AIO_INFLATTER_ERROR"

#define AIO_INFLATTER_INFO_TAG "AIO_INFLATTER_INFO"

#ifdef AIO_INFLATTER_DEBUG

#include <cstdlib>
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>

#endif

/**
 * 비즈니스 로직.
 */

#define AIO_BUILD_SCRIPT_FORMAT ".aio_core"

#define AIO_SUFFIX ".aio"

using namespace lib4aio;

static void inflate_aio_file(aio_core *core, const str_hook *file_path)
{

}

static aio_build_script_space *extract_build_script_materials(const str_builder *script_string_builder)
{
    const bool has_content = script_string_builder->size() > 0;
    if (has_content) {
        const char *build_script_content = script_string_builder->get_string();
        const unsigned build_script_content_length = script_string_builder->size();
        str_hook *build_script_holder = new str_hook(build_script_content, 0, build_script_content_length);
        //Create build script orbit:
        aio_orbit<aio_build_script_space> *script_orbit = new aio_build_script_orbit();
        aio_build_script_space *materials = script_orbit->launch(build_script_holder);
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기:
        delete script_orbit;
        //--------------------------------------------------------------------------------------------------------------
        return materials;
    } else {
        throw_error_with_tag(AIO_INFLATTER_ERROR_TAG, "파일 내용 비어있습니다");
    }
}

str_hook *inflate_aio_context(aio_core *core, const char *build_script_path)
{
    if (ends_with_suffix(build_script_path, AIO_BUILD_SCRIPT_FORMAT)) {
        str_builder *file_string_builder = read_file_by_str_builder(build_script_path);
#ifdef AIO_INFLATTER_DEBUG
        log_info_string(AIO_INFLATTER_INFO_TAG, "aio build script: \n", file_string_builder->get_string());
#endif
        aio_build_script_space *build_script_materials = extract_build_script_materials(file_string_builder);
        str_hook *main_path = build_script_materials->program_entry;
        core->set_script_builder(file_string_builder);
        inflate_aio_file(core, main_path);
        return main_path;
    } else {
        throw_error_with_details(AIO_INFLATTER_ERROR_TAG, "파일이 '*.aio_core' 형식이 아닙니다", build_script_path);
    }
}