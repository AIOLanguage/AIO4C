#ifndef FILE_READER_H
#define FILE_READER_H

const struct str_hook *extract_name_from_path(const char *path);

char *read_file_and_join_to_string_without_comments(const char *path);

#endif //FILE_READER_H