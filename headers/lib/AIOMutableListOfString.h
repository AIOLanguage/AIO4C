#ifndef AIO_AIO_MUTABLE_LIST_H
#define AIO_AIO_MUTABLE_LIST_H

//Passed JUnitTests!
typedef struct AIOMutableListOfString {
    int size;
    char strings[256][256];
} AIOMutableListOfString;

AIOMutableListOfString mutableListOfString();

void addInMutableListOfString(struct AIOMutableListOfString* listOfString, const char name[]);

char* getStringInMutableListByIndex(struct AIOMutableListOfString *listOfString, int index);

#endif