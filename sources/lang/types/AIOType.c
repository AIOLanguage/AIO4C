#include <ctype.h>
#include <stdio.h>
#include <mem.h>

//Passed JUnitTest!
int matchesInt(const char word[]) {
    for (int i = 0; i < strlen(word); ++i) {
        const int e = word[i] - '0';
        if (e < 0 || e > 9) {
            return -1;
        }
    }
    return 0;
}

//Passed JUnitTest!
int matchesDou(const char word[]) {
    int wasDot = -1;
    int wasFraction = -1;
    for (int i = 0; i < strlen(word); ++i) {
        const int e = word[i] - '0';
        if ((e < 0 || e > 9)) {
            if (word[i] == '.' && wasDot == -1) {
                wasDot = 0;
            } else {
                return -1;
            }
        }
        if (e > 0 && e < 10 && wasDot == 0) {
            wasFraction = 0;
        }
    }
    if (wasDot == 0 && wasFraction == 0) {
        return 0;
    } else {
        return -1;
    }
}

int matchesCha(const char word[]){
    if (strlen(word) == 1){
        return 0;
    } else {
        return -1;
    }
}

int matchesStr(const char word[]){
    if (strlen(word) != 1){
        return 0;
    } else {
        return -1;
    }
}