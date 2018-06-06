#include <ctype.h>
#include <stdio.h>
#include <mem.h>
#include <comip.h>

//Passed JUnitTest!
int matchesInt(char* word) {
    int start = 0;
    int length = strlen(word);
    if (length == 0){
        free(&start);
        free(&length);
        printf("empty string as Int!");
        exit(1);
    }
    if (word[0] == '-'){
        if (length == 1){
            free(&start);
            free(&length);
            printf("this is a minus as Int!");
            exit(1);
        }
        start = 1;
    }
    for (int i = start; i < strlen(word); ++i) {
        int e = word[i] - '0';
        if (e < 0 || e > 9) {
            free(&length);
            free(&start);
            return -1;
        }
        free(&e);
    }
    free(&length);
    free(&start);
    return 0;
}

//Passed JUnitTest!
int matchesDou(char* word) {
    int result = -1;
    int wasDot = -1;
    int wasFraction = -1;
    int start = 0;
    int length = strlen(word);
    if (length == 0){
        free(&start);
        free(&length);
        printf("empty string as Dou!");
        exit(1);
    }
    if (word[0] == '-'){
        if (length == 1){
            free(&start);
            free(&length);
            printf("this is a minus as Dou!");
            exit(1);
        }
        start = 1;
    }
    for (int i = start; i < strlen(word); ++i) {
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

//Passed JUnitTest!
int matchesCha(char* word){
    int result = -1;
    int length = strlen(word);
    if (length == 3 && word[0] == '\'' && word[length - 1] == '\''){
        result = 0;
    }
    free(&length);
    return result;
}

//Passed JUnitTest!
int matchesStr(char* word){
    int result = -1;
    int length = strlen(word);
    if ((length == 2 || length > 3) && word[0] == '\'' && word[length - 1] == '\''){
        result = 0;
    }
    free(&length);
    return result;
}