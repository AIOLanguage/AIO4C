#ifndef AIO_RESULT_H
#define AIO_RESULT_H

typedef struct aio_int_result {
    int acc;
    char *rest;
} aio_int_result;

void new_aio_int_result(aio_int_result **result, int acc, char *rest);

typedef struct aio_dou_result {
    double acc;
    char *rest;
} aio_dou_result;

void new_aio_dou_result(aio_dou_result **result, double acc, char *rest);

typedef struct aio_cha_result {
    char acc;
    char *rest;
} aio_cha_result;

void new_aio_cha_result(aio_cha_result **result, char acc, char *rest);

typedef struct aio_str_result {
    char *acc;
    char *rest;
} aio_str_result;

void new_aio_str_result(aio_str_result **result, char *acc, char *rest);

#endif //AIO_RESULT_H