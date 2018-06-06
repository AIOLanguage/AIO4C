#include "../../../../headers/lib/collections/lists/AIOMutableListOfString.h"
#include <string.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>

void createMutableListOfString(AIOMutableListOfString **listOfString) {
    //Create the same mutable list:
    *listOfString = malloc(sizeof(AIOMutableListOfString));
    //Create capacity:
    (*listOfString)->capacity = malloc(sizeof(int));
    *(*listOfString)->capacity = 2;
    //Create size:
    (*listOfString)->size = malloc(sizeof(int));
    *(*listOfString)->size = 0;
    //Create char capacity that equals 2:
    (*listOfString)->strings = malloc(2 * sizeof(char));
}

void updateMemoryInMutableListOfString(AIOMutableListOfString *listOfString) {
    if (*listOfString->size + 1 == *listOfString->capacity) {
        *listOfString->capacity = *listOfString->capacity * 2;
        listOfString->strings = realloc(listOfString->strings, *listOfString->capacity * sizeof(char));
    }
}

//Passed JUnitTests!
void addInMutableListOfString(AIOMutableListOfString *listOfString, char *string) {
    //Check to update capacity:
    updateMemoryInMutableListOfString(listOfString);
    //Set string:
    listOfString->strings[*listOfString->size] = malloc(strlen(string));
    listOfString->strings[*listOfString->size] = string;
    printf("%s\n", listOfString->strings[*listOfString->size]);
    *listOfString->size = *listOfString->size + 1;
    printf("%d\n", *listOfString->size);
}

//Passed JUnitTests!
char *getStringInMutableListByIndex(AIOMutableListOfString *listOfString, int *index) {
    if (*index < 0 || *listOfString->size < *index) {
        printf("Cannot get index: %d in MutableList", *index);
        exit(1);
    } else {
        return listOfString->strings[*index];
    }
}
