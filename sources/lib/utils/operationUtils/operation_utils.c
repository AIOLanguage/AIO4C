#include <mem.h>

int is_plus_operation(char *string) {
    if (strlen(string)){
        if (string[0] == '+'){
            return 0;
        }
    }
    return -1;
}

int is_multiply_operation(char *string) {
    if (strlen(string)){
        if (string[0] == '*'){
            return 0;
        }
    }
    return -1;
}

int is_concat_operation(char *string) {
    if (strlen(string)){
        if (string[0] == '&'){
            return 0;
        }
    }
    return -1;
}

int isDefaultOperations(const char *string) {
    if (strlen(string) == 1) {
        if (string[0] == '+' || string[0] == '*' || string[0] == '&') {
            return 0;
        }
    }
    return -1;
}