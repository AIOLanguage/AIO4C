#ifndef AIO_STRING_UTILS_H
#define AIO_STRING_UTILS_H

#include <stddef.h>

//끝난!
int split_by_char(const char *src, char delimiter, char ***dst);

int trim_start(const char *src, char **dst);

int trim_end(const char *src, char **dst);

int trim(const char *src, char **dst);

int is_white_space(char src);

void trim_all(char **strings, int number_of_strings, char ***dst);

int remove_prefix(const char *src, const char *prefix, char **dst);

int remove_suffix(const char *src, const char *suffix, char **dst);

int remove_prefix_suffix(const char *src, const char *prefix, const char *suffix, char **dst);

int starts_with(const char *src, char *prefix);

int ends_with(const char *src, char *suffix);

int **filter(char **src, size_t srcSize, char ***dst, int (*filterFunction)(char *));

int is_not_empty_string(char *string);

int is_empty_string(char *string);

void join_to_string_without_spaces(char **srcStrings, char **dst);

int join_to_string(char **srcStrings, char *delimiter, char **dst);

int is_word(char *line);

void substring(const char *string, int offset, int length, char **dst);

void concat_string_to_string(char *src, char **dst);

void concat_char_to_string(char src, char **dst);

#endif //AIO_STRING_UTILS_H