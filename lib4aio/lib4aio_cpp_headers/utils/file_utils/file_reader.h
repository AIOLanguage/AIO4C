#ifndef LIB4AIO_FILE_READER_H
#define LIB4AIO_FILE_READER_H

namespace lib4aio {

    class str_hook;

    const str_hook *extract_name_from_path(const char *path);

    const char *read_file_and_join_to_string_without_comments(const char *path);
}

#endif //LIB4AIO_FILE_READER_H