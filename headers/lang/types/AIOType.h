#ifndef AIO_AIO_TYPE_H
#define AIO_AIO_TYPE_H
enum AIOType {
    AIO_INT, AIO_DOU, AIO_CHA, AIO_STR
};

int matchesInt(char* word);

void toInt(char* word, void** dst);

int matchesDou(char* word);

double toDou(char* word, void** dst);

int matchesCha(char* word);

char toCha(char* word, void** dst);

int matchesStr(char* word);

char* toStr(char* word, void** dst);

void setType(char *value, enum AIOType *type);

int isAIOIntType(enum AIOType type);

#endif //AIO_AIO_TYPE_H