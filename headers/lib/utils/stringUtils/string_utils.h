#ifndef AIO_STRING_UTILS_H
#define AIO_STRING_UTILS_H

#include <stddef.h>

char** split_by_string(const char *src, const char *delimiter); //끝난!

char* trim_start(const char *src);

char* trim_end(const char *src);

char* trim(const char *src);

int is_white_space(char src);

char** trim_all(char **strings, int number_of_strings);

char *remove_prefix(const char *src, const char *prefix); //끝난!

char *remove_suffix(const char *src, const char *suffix); //끝난!

char *remove_prefix_suffix(const char *src, const char *prefix, const char *suffix);

int starts_with_prefix(const char *src, char *prefix);

int ends_with_suffix(const char *src, char *suffix);

int filter(char **src, size_t srcSize, char ***dst, int (*filterFunction)(char *));

int is_not_empty_string(char *string);

int is_empty_string(char *string);

void join_to_string_without_spaces(char **srcStrings, char **dst);

int join_to_string(char **srcStrings, char *delimiter, char **dst);

int is_word(char *line);

void substring(const char *string, int offset, int length, char **dst);

void concat_string_to_string(char *src, char **dst);

void concat_char_to_string(char src, char **dst);

#endif //AIO_STRING_UTILS_H