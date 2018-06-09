#include <mem.h>

int isPlusOperation(char *string) {
    if (strlen(string)){
        if (string[0] == '+'){
            return 0;
        }
    }
    return -1;
}

int isMultiplyOperation(char *string) {
    if (strlen(string)){
        if (string[0] == '*'){
            return 0;
        }
    }
    return -1;
}

int isConcatOperation(char *string) {
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