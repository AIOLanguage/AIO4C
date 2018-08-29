#ifndef STRING_PAIR_H
#define STRING_PAIR_H

typedef struct string_pair {
    char *first;
    char *second;
} string_pair;

struct string_pair *new_string_pair(char *first, char *second);

#endif //STRING_PAIR_H