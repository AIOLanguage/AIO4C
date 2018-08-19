#include <mem.h>
#include <malloc.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/utils/string_pair/string_pair.h"
#include "../../../../headers/lib/utils/memory_utils/memory_utils.h"

string_pair* new_string_pair(char* first, char* second){
    string_pair* pair = new_object(sizeof(pair));
    if (pair == NULL){
        perror("cannot allocate memory for  string_pair");
        exit(1);
    }
    pair->first = first;
    pair->second = second;
    return pair;
}