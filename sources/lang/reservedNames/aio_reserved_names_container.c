#include <stdio.h>
#include <string.h>

//Done!
char reservedNames[5][4] = {
        {"im"},
        {"int"},
        {"dou"},
        {"cha"},
        {"str"}};

//Passed JUnitTest!
int can_use_name(char *name) {
    for (int i = 0; i < 5; i++) {
        printf("%s\n", reservedNames[i]);
        if (strcmp(name, reservedNames[i]) == 0) {
            return -1;
        }
    }
    return 0;
}