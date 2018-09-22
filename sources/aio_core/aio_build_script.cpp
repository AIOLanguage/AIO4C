#include <cstdlib>
#include <aio_core/aio_build_script.h>
#include <lib4aio_cpp_headers/utils/memory_utils/memory_utils.h>
#include <lib4aio_cpp_headers/utils/string_utils/common.h>

using namespace lib4aio;

aio_build_script_space *new_aio_build_script_materials()
{
    aio_build_script_space *build_script_space = (aio_build_script_space *) new_object(sizeof(aio_build_script_space));
    return build_script_space;
}

void free_aio_build_script_materials(const aio_build_script_space *materials)
{
    free((void *) materials->main_path);
    free((void *) materials);
}
