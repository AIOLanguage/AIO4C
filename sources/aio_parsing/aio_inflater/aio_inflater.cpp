#include <aio_core/aio_core.h>
#include <lib4aio_cpp_headers/utils/file_utils/file_reader.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

using namespace lib4aio;

static void inflate_aio_file(aio_core *core, const str_hook *file_path)
{

}

static const str_hook *get_program_entry_by_script(const char *aio_build_data)
{

}

const str_hook *inflate_aio_context(aio_core *core, const char *build_script_path)
{
    const char *build_script_data = get_source_code_by_file_path(build_script_path);
    const str_hook *main_path = get_program_entry_by_script(build_script_data);
    core->set_build_script_data(build_script_data);
    inflate_aio_file(core, main_path);
    return main_path;
}