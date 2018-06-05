#include "../../../headers/lib/lists/AIOMutableListOfString.h"
#include <string.h>
#include <process.h>
#include <stdio.h>
#include <malloc.h>

void createMutableListOfString(AIOMutableListOfString **listOfString) {
    *listOfString = (AIOMutableListOfString *) calloc(1, sizeof(AIOMutableListOfString));
    *(*listOfString)->size = 0;
}

//Passed JUnitTests!
void addInMutableListOfString(AIOMutableListOfString *listOfString, const char *string) {
    strcpy(listOfString->strings[*listOfString->size], string);
    listOfString->size++;
}

//Passed JUnitTests!
char *getStringInMutableListByIndex(struct AIOMutableListOfString *listOfString, int index) {
    if (index < 0 || *listOfString->size < index) {
        printf("Cannot get index: %d in MutableList", index);
        exit(1);
    } else {
        return listOfString->strings[index];
    }
}