#ifndef AIO_AIO_TYPE_H
#define AIO_AIO_TYPE_H
enum AIOType {
    AIO_INT, AIO_DOU, AIO_CHA, AIO_STR
};

int matchesInt(const char word[]);

int toInt(const char word[]);

int matchesDou(const char word[]);

double toDou(const char word[]);

int matchesCha(const char word[]);

char toCha(const char word[]);

int matchesStr(const char word[]);

char* toStr(const char word[]);
#endif //AIO_AIO_TYPE_H