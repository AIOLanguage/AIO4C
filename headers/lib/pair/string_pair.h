#ifndef AIO_STRING_PAIR_H
#define AIO_STRING_PAIR_H

typedef struct string_pair {
    char* first;
    char* second;
} string_pair;

string_pair* new_string_pair(char* first, char* second);

#endif //AIO_STRING_PAIR_H