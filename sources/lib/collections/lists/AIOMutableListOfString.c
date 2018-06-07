#include "../../../../headers/lib/collections/lists/AIOMutableListOfString.h"
#include <string.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>

//Passed JUnitTest!
void createMutableListOfString(AIOMutableListOfString **listOfString) {
    //Create the same mutable list:
    *listOfString = calloc(1, sizeof(AIOMutableListOfString));
    //Create capacity:
    (*listOfString)->capacity = calloc(1, sizeof(int));
    if ((*listOfString)->capacity == NULL){
        perror("can not allocate memory for capacity in mutable list of string");
    }
    *(*listOfString)->capacity = 2;
    //Create size:
    (*listOfString)->size = calloc(1, sizeof(int));
    if ((*listOfString)->size == NULL){
        perror("can not allocate memory for size in mutable list of string");
    }
    *(*listOfString)->size = 0;
    //Create char capacity that equals 2:
    (*listOfString)->strings = calloc(2, sizeof(char*));
    if ((*listOfString)->strings == NULL){
        perror("can not allocate memory for strings in mutable list of string");
    }
}

//Passed JUnitTest!
void updateMemoryInMutableListOfString(AIOMutableListOfString *listOfString) {
    if (*listOfString->size + 1 == *listOfString->capacity) {
        *listOfString->capacity = *listOfString->capacity * 2;
        listOfString->strings = realloc(listOfString->strings, *listOfString->capacity * sizeof(char*));
    }
}

//Passed JUnitTests!
void addInMutableListOfString(AIOMutableListOfString *listOfString, char *string) {
    //Check to update capacity:
    updateMemoryInMutableListOfString(listOfString);
    //Set string:
    listOfString->strings[*listOfString->size] = calloc(1, strlen(string));
    listOfString->strings[*listOfString->size] = string;
    *listOfString->size = *listOfString->size + 1;
}

//Passed JUnitTests!
char *getStringInMutableListByIndex(AIOMutableListOfString *listOfString, int index) {
    if (index < 0 || *listOfString->size <= index) {
        perror("Cannot get index: %d in MutableList");
        exit(1);
    } else {
        return listOfString->strings[index];
    }
}
