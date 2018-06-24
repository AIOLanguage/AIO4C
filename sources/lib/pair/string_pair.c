#include <mem.h>
#include <malloc.h>
#include <stdio.h>
#include <process.h>
#include "../../../headers/lib/pair/string_pair.h"

string_pair* new_string_pair(char* first, char* second){
    string_pair* pair = calloc(1, sizeof(pair));
    if (pair == NULL){
        perror("cannot allocate memory for  string_pair");
        exit(1);
    }
    pair->first = first;
    pair->second = second;
}