#include <lib4aio_cpp_headers/utils/point_watcher/point_watcher.h>

namespace lib4aio
{

#ifndef LIB4AIO_STR_POINT_WATCHER_H
#define LIB4AIO_STR_POINT_WATCHER_H

    class str_point_watcher : public point_watcher
    {
    public:

        const char *source_string;

        str_point_watcher(const char *source_string);

        ~str_point_watcher();
    };

#endif //LIB4AIO_STR_POINT_WATCHER_H

}