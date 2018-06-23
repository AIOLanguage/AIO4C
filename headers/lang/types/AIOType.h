#ifndef AIO_AIO_TYPE_H
#define AIO_AIO_TYPE_H
enum AIOType {
    AIO_INT, AIO_DOU, AIO_CHA, AIO_STR
};

typedef int AIOInt;

typedef double AIODou;

typedef char AIOCha;

typedef char* AIOStr;

int matchesInt(char* word);

void strToInt(char *word, int **dst);

int matchesDou(char* word);

void strToDou(char *word, double **dst);

int matchesCha(char* word);

char strToCha(char *word, void **dst);

int matchesStr(char* word);

void setType(char *value, enum AIOType *type);

int isAIOIntType(enum AIOType type);

void intToStr(int src, char **dst);

void douToStr(double src, char **dst);

void chaToStr(char src, char **dst);

#endif //AIO_AIO_TYPE_H