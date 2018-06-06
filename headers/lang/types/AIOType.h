#ifndef AIO_AIO_TYPE_H
#define AIO_AIO_TYPE_H
enum AIOType {
    AIO_INT, AIO_DOU, AIO_CHA, AIO_STR
};

int matchesInt(char* word);

int toInt(char* word);

int matchesDou(char* word);

double toDou(char* word);

int matchesCha(char* word);

char toCha(char* word);

int matchesStr(char* word);

char* toStr(char* word);
#endif //AIO_AIO_TYPE_H