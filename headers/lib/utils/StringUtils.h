#ifndef AIO_STRING_UTILS_H
#define AIO_STRING_UTILS_H

char **split(char *string, char delimiter);

int trimStart(const char *src, char **dst);

int trimEnd(const char *src, char **dst);

int trim(const char *src, char **dst);

#endif //AIO_STRING_UTILS_H