#ifndef STRING_LIST_H
#define STRING_LIST_H

//Passed JUnitTests!
typedef struct StringList {
    int* capacity;
    int* size;
    char** strings;
} StringList;

void createStringList(StringList **listOfString);

void addInStringList(StringList *listOfString, char *);

char* getStringInListByIndex(StringList *listOfString, int index);

int isStringListEmpty(StringList* listOfString);

#endif //STRING_LIST_H