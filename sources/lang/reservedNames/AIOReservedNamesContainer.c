#include <string.h>

char *reservedNames[5];

void initRecervedNamesContainer() {
    reservedNames[0] = "im";
    reservedNames[1] = "int";
    reservedNames[2] = "dou";
    reservedNames[3] = "cha";
    reservedNames[4] = "str";
}

int canUseName(char* name) {
    for (int i = 0; i < sizeof(reservedNames); i++){
        if (strcmp(name, reservedNames[i]) != 0){
            return -1;
        }
    }
    return 0;
}