#include <lib4aio_cpp_headers/utils/point_watcher/str_hook_watcher/str_point_watcher.h>

namespace lib4aio
{

    str_point_watcher::str_point_watcher(const char *source_string) : point_watcher()
    {
        this->source_string = source_string;
    };

    str_point_watcher::~str_point_watcher()
    {}
}