#ifndef FILE_READER_H
#define FILE_READER_H

#include "../string_utils/string_utils.h"
#include "../str_hook/str_hook.h"

const struct str_hook *extract_name_from_path(const char *path);

const char *read_file_and_join_to_string_without_comments(const char *path);

#endif //FILE_READER_H