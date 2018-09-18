#include <aio_core/aio_core.h>
#include <lib4aio_cpp_headers/utils/file_utils/file_reader.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

using namespace lib4aio;

str_hook *inflate_aio_context_for(aio_core *core, const char *path)
{
    const char *build_data = read_file_and_join_to_string_without_comments(path);
}