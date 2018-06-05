#ifndef AIO_AIO_MUTABLE_LIST_H
#define AIO_AIO_MUTABLE_LIST_H

//Passed JUnitTests!
typedef struct AIOMutableListOfString {
    int* size;
    char** strings;
} AIOMutableListOfString;

void createMutableListOfString(AIOMutableListOfString** listOfString);

void addInMutableListOfString(AIOMutableListOfString* listOfString, const char*);

char* getStringInMutableListByIndex(AIOMutableListOfString *listOfString, int index);

#endif