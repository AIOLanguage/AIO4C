#ifndef FILE_READER_H
#define FILE_READER_H

#include "../string_utils/string_utils.h"
#include "../str_hook/str_hook.h"

const_str_hook *extract_name_from_path(const_string path);

const_string read_file_and_join_to_string_without_comments(const_string path);

#endif //FILE_READER_H