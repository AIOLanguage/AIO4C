#include <stdio.h>
#include <string.h>

//Done!
char reserved_names[5][4] = {
        {"im"},
        {"int"},
        {"dou"},
        {"cha"},
        {"str"}};

//Passed JUnitTest!
int can_use_name(char *name) {
    for (int i = 0; i < 5; i++) {
        printf("%s\n", reserved_names[i]);
        if (strcmp(name, reserved_names[i]) == 0) {
            return -1;
        }
    }
    return 0;
}