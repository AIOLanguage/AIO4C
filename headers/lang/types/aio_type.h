#ifndef AIO_AIO_TYPE_H
#define AIO_AIO_TYPE_H
enum aio_type {
    AIO_INT, AIO_DOU, AIO_CHA, AIO_STR
};

typedef int aio_int;

typedef double aio_dou;

typedef char aio_cha;

typedef char *aio_str;

int matches_int(char *word);

int str_to_int(char *word);

int matches_dou(char *word);

double str_to_dou(char *word);

int matches_cha(char *word);

char str_to_cha(char *word);

int matches_str(char *word);

void set_type(char *value, enum aio_type *type);

int is_aio_int_type(enum aio_type type);

char* int_to_str(int src);

char* dou_to_str(double src);

char* cha_to_str(char src);

#endif //AIO_AIO_TYPE_H