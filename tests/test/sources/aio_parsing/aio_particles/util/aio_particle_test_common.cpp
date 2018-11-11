//native:
#include <cstdio>
//lib4aio:
#include <lib4aio_cpp_headers/utils/log_utils/log_utils.h>
#include <lib4aio_cpp_headers/utils/color_utils/color_utils.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

using namespace lib4aio;

void print_radius(const char * tag, const str_hook *radius)
{
    log_info(tag, "\n---------------------------");
    log_info_str_hook(tag, "SAMPLE: \n\n" GREEN, radius);
    printf(RESET);
    log_info(tag, "\n-------------------------\n");
}