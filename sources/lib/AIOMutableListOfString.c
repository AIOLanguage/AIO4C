#include "../../headers/lib/AIOMutableListOfString.h"
#include <string.h>
#include <process.h>
#include <stdio.h>

//Passed JUnitTests!
AIOMutableListOfString mutableListOfString() {
    struct AIOMutableListOfString newList = {.size = 0};
    return newList;
}

//Passed JUnitTests!
void addInMutableListOfString(struct AIOMutableListOfString* listOfString, const char name[]) {
    const int index = listOfString->size;
    strcpy(listOfString->strings[index], name);
    listOfString->size++;
}

//Passed JUnitTests!
char* getStringInMutableListByIndex(struct AIOMutableListOfString *listOfString, int index){
    if (index < 0 || listOfString->size < index){
        printf("Cannot get index: %d in MutableList", index);
        exit(1);
    } else {
        return listOfString->strings[index];
    }
}