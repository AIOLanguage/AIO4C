#include <cstdlib>
#include <aio_core/aio_core.h>
#include <aio_core/aio_build_script.h>
#include <aio_parsing/aio_orbits/aio_build_script/aio_build_script_orbit.h>
#include <lib4aio_cpp_headers/aio_orbit/aio_orbit.h>
#include <lib4aio_cpp_sources/aio_orbit/aio_orbit.cpp>
#include <lib4aio_cpp_headers/utils/file_utils/file_reader.h>
#include <lib4aio_cpp_headers/utils/str_builder/str_builder.h>
#include <lib4aio_cpp_headers/utils/error_utils/error_utils.h>
#include <lib4aio_cpp_headers/utils/string_utils/suffix_prefix.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

#define AIO_INFLATTER_DEBUG

#define AIO_INFLATTER_ERROR_TAG "AIO_INFLATTER_ERROR"

#define AIO_INFLATTER_INFO_TAG "AIO_INFLATTER_INFO"

#ifdef AIO_INFLATTER_DEBUG

#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>
#include <lib4aio_cpp_headers/utils/pair/pair.h>
#include <cstring>
#include <lib4aio_cpp_headers/utils/char_utils/char_utils.h>

#endif

/**
 * 비즈니스 로직.
 */

#define AIO_BUILD_SCRIPT_FORMAT ".aio_core"

#define AIO_SUFFIX ".aio"

using namespace lib4aio;

static char *make_absolute_path(const str_hook *file_path_holder, const char *build_script_path)
{
    const char *source_file_path_string = file_path_holder->get_string();
    str_builder *sb = new str_builder();
    sb->append(build_script_path);
    sb->append('/');
    for (unsigned i = file_path_holder->start; i < file_path_holder->end; ++i) {
        const char symbol = source_file_path_string[i];
        if (is_dot(symbol)) {
            sb->append('/');
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

static void inflate_aio_file(
        str_hook *file_path_holder,
        const char *build_script_path,
        array_list<aio_file> *file_collection
)
{
    const bool is_contains_file = file_collection->contains_by([&file_path_holder] {
        it->file_entry->first.equals(file_path_holder);
    });
    if (!is_contains_file) {
        char *absolute_path = make_absolute_path(file_path_holder, build_script_path);
        const pair<str_hook, char> *relative_vs_absolute_path = new pair(file_path_holder, absolute_path);
        const str_hook *absolute_path_holder = new str_hook(absolute_path);
        //Create file orbit:
        aio_orbit<aio_file_space> *file_orbit = new aio_file_orbit(file_collection);
        aio_file *file = file_orbit->launch(absolute_path_holder);
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼끼 수집기:
        delete absolute_path_holder;
        delete file_orbit;
        //--------------------------------------------------------------------------------------------------------------
        file_collection->add(file);
    }
}

static array_list<aio_file> *inflate_aio_files(str_hook *file_path_holder, const char *build_script_path)
{
    array_list<aio_file> *file_collection = new array_list<aio_file>();
    inflate_aio_file(file_path_holder, build_script_path, file_collection);
    return file_collection;
}

static aio_build_script_space *extract_build_script_materials(const str_builder *script_string_builder)
{
    const bool has_content = script_string_builder->size() > 0;
    if (has_content) {
#ifdef AIO_INFLATTER_DEBUG
        log_info(AIO_INFLATTER_INFO_TAG, "HAS CONTENT!");
#endif
        const char *build_script_content = script_string_builder->get_string();
        const unsigned build_script_content_length = script_string_builder->size();
        const str_hook *build_script_holder = new str_hook(build_script_content, 0, build_script_content_length);
        //Create build script orbit:
        aio_orbit<aio_build_script_space> *script_orbit = new aio_build_script_orbit();
        aio_build_script_space *materials = script_orbit->launch(build_script_holder);
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기:
        delete build_script_holder;
        delete script_orbit;
        //--------------------------------------------------------------------------------------------------------------
        return materials;
    } else {
        throw_error_with_tag(AIO_INFLATTER_ERROR_TAG, "파일 내용 비어있습니다");
    }
}

const str_hook *inflate_aio_context_for(aio_core *core, const char *build_script_path)
{
    const bool is_aio_build_script_file = ends_with_suffix(build_script_path, AIO_BUILD_SCRIPT_FORMAT);
    if (is_aio_build_script_file) {
        str_builder *file_string_builder = read_file_by_str_builder(build_script_path);
#ifdef AIO_INFLATTER_DEBUG
        log_info_string(AIO_INFLATTER_INFO_TAG, "아이어 빌드 스크립트: \n", file_string_builder->get_string());
#endif
        const aio_build_script_space *build_script_materials = extract_build_script_materials(file_string_builder);
        const char *main_path_string = build_script_materials->main_path;
        str_hook *main_path_holder = new str_hook(main_path_string);
#ifdef AIO_INFLATTER_DEBUG
        log_info_str_hook(AIO_INFLATTER_INFO_TAG, "EXTRACTED MAIN PATH:", main_path_holder);
#endif
        array_list<aio_file> *files = inflate_aio_files(main_path_holder, build_script_path);
        core->set_build_script_materials(build_script_materials);
        core->set_aio_file_list(files);
        return main_path_holder;
    } else {
        throw_error_with_details(AIO_INFLATTER_ERROR_TAG, "파일이 '*.aio_core' 형식이 아닙니다", build_script_path);
    }
}