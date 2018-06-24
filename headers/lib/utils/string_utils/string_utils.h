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

char** filter(char **src, int src_size, int (*filterFunction)(char *));

int is_not_empty_string(char *string);

int is_empty_string(char *string);

char* join_to_string(char **srcStrings, char *delimiter, int src_size);

int is_word(char *line);

char* substring(const char *string, int offset, int length);

void concat_string_to_string(char *dst, char *src);

void concat_char_to_string(char *dst, char src);

#endif //AIO_STRING_UTILS_H