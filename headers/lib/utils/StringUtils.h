#ifndef AIO_STRING_UTILS_H
#define AIO_STRING_UTILS_H

char **split(char *string, char delimiter);

int trimStart(const char *src, char **dst);

int trimEnd(const char *src, char **dst);

int trim(const char *src, char **dst);

int removePrefix(const char *src, const char *prefix, char **dst);

int removeSuffix(const char *src, const char *suffix, char **dst);

#endif //AIO_STRING_UTILS_H