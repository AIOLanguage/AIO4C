#include <ctype.h>
#include <stdio.h>
#include <mem.h>
#include <comip.h>

//Passed JUnitTest!
int matchesInt(char* word) {
    for (int i = 0; i < strlen(word); ++i) {
        const int e = word[i] - '0';
        if (e < 0 || e > 9) {
            return -1;
        }
    }
    return 0;
}

//Passed JUnitTest!
int matchesDou(char* word) {
    int result = -1;
    int wasDot = -1;
    int wasFraction = -1;
    for (int i = 0; i < strlen(word); ++i) {
        int e = word[i] - '0';
        if ((e < 0 || e > 9)) {
            if (word[i] == '.' && wasDot == -1) {
                wasDot = 0;
            } else {
                return -1;
            }
        }
        if (e >= 0 && e < 10 && wasDot == 0) {
            wasFraction = 0;
        }
        free(&e);
    }
    if (wasDot == 0 && wasFraction == 0) {
        result = 0;
    }
    free(&wasDot);
    free(&wasFraction);
    return result;
}

int matchesCha(char* word){
    int result = -1;
    int length = strlen(word);
    if (length == 3 && word[0] == '\'' && word[length - 1] == '\''){
        result = 0;
    }
    free(&length);
    return result;
}

int matchesStr(char* word){
    int result = -1;
    int length = strlen(word);
    if ((length == 2 || length > 3) && word[0] == '\'' && word[length - 1] == '\''){
        result = 0;
    }
    free(&length);
    return result;
}