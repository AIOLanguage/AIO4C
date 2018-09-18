#ifndef LIB4AIO_FILE_READER_H
#define LIB4AIO_FILE_READER_H

namespace lib4aio {

    class str_hook;

    const str_hook *get_name_by_file_path(const char *path);

    const char *get_source_code_by_file_path(const char *path);
}

#endif //LIB4AIO_FILE_READER_H