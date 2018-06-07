#ifndef AIO_STRING_UTILS_H
#define AIO_STRING_UTILS_H

char **split(char *string, char delimiter);

int trimStart(const char *src, char **dst);

int trimEnd(const char *src, char **dst);

int trim(const char *src, char **dst);

int removePrefix(const char *src, const char *prefix, char **dst);

int removeSuffix(const char *src, const char *suffix, char **dst);

int startsWith(const char *src, char *prefix);

int **filter(char **src, size_t srcSize, char*** dst, int (*filterFunction)(char *));

int isNotEmpty(char *string);

void joinToStringWithoutSpaces(char **srcStrings, char **dst);

int joinToString(char **srcStrings, char* delimiter, char **dst);

int isWord(char *line);

#endif //AIO_STRING_UTILS_H