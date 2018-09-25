#include <lib4aio_cpp_headers/aio_path_util/aio_path_util.h>
#include <lib4aio_cpp_headers/utils/char_utils/char_utils.h>
#include <lib4aio_cpp_headers/utils/str_builder/str_builder.h>
#include <lib4aio_cpp_headers/utils/str_hook_utils/str_hook/str_hook.h>

#define SLASH_SYMBOL '/'

#define AIO_FILE_FORMAT ".aio"

namespace lib4aio {

    char *construct_absolute_path(const str_hook *relative_path, const char *script_path)
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
        sb->append(AIO_FILE_FORMAT);
        char *absolute_path = sb->pop();
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기:
        delete sb;
        //--------------------------------------------------------------------------------------------------------------
        return absolute_path;
    }

    char *construct_absolute_path(const char *relative_path, const char *script_path)
    {
        str_builder *sb = new str_builder();
        sb->append(script_path);
        sb->append(SLASH_SYMBOL);
        sb->append(relative_path);
        sb->append(AIO_FILE_FORMAT);
        char *absolute_path = sb->pop();
        //--------------------------------------------------------------------------------------------------------------
        //찌꺼기 수집기:
        delete sb;
        //--------------------------------------------------------------------------------------------------------------
        return absolute_path;
    }
}