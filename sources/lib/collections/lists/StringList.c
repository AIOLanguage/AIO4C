#include "../../../../headers/lib/collections/lists/StringList.h"
#include <string.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

//Passed JUnitTest!
void createListOfString(StringList **listOfString) {
    //Create the same mutable list:
    *listOfString = calloc(1, sizeof(StringList));
    //Create capacity:
    (*listOfString)->capacity = calloc(1, sizeof(int));
    if ((*listOfString)->capacity == NULL) {
        perror("can not allocate memory for capacity in mutable list of string");
    }
    *(*listOfString)->capacity = 2;
    //Create size:
    (*listOfString)->size = calloc(1, sizeof(int));
    if ((*listOfString)->size == NULL) {
        perror("can not allocate memory for size in mutable list of string");
    }
    *(*listOfString)->size = 0;
    //Create char capacity that equals 2:
    (*listOfString)->strings = calloc(2, sizeof(char *));
    if ((*listOfString)->strings == NULL) {
        perror("can not allocate memory for strings in mutable list of string");
    }
}

//Passed JUnitTest!
void updateMemoryInListOfString(StringList *listOfString) {
    if (*listOfString->size + 1 == *listOfString->capacity) {
        *listOfString->capacity = *listOfString->capacity * 2;
        listOfString->strings = realloc(listOfString->strings, *listOfString->capacity * sizeof(char *));
    }
}

//Passed JUnitTests!
void addInListOfString(StringList *listOfString, char *string) {
    //Check to update capacity:
    updateMemoryInListOfString(listOfString);
    //Set string:
    listOfString->strings[*listOfString->size] = calloc(1, sizeof(string));
    listOfString->strings[*listOfString->size] = string;
    *listOfString->size = *listOfString->size + 1;
}

//Passed JUnitTests!
char *getStringInListByIndex(StringList *listOfString, int index) {
    if (index < 0 || *listOfString->size <= index) {
        perror("Cannot get index: %d in MutableList");
        exit(1);
    } else {
        return listOfString->strings[index];
    }
}

int isStringListEmpty(StringList *listOfString) {
    if (*listOfString->size == 0) {
        return 0;
    } else {
        return -1;
    }
}