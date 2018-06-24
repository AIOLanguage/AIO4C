#ifndef AIO_AIO_TYPE_H
#define AIO_AIO_TYPE_H
enum aio_type {
    AIO_INT, AIO_DOU, AIO_CHA, AIO_STR
};

typedef int aio_int;

typedef double aio_dou;

typedef char AIOCha;

typedef char* aio_str;

int matchesInt(char* word);

void str_to_int(char *word, int **dst);

int matchesDou(char* word);

void str_to_dou(char *word, double **dst);

int matchesCha(char* word);

char strToCha(char *word, void **dst);

int matchesStr(char* word);

void setType(char *value, enum aio_type *type);

int isAIOIntType(enum aio_type type);

void int_to_str(int src, char **dst);

void dou_to_str(double src, char **dst);

void chaToStr(char src, char **dst);

#endif //AIO_AIO_TYPE_H