#ifndef AIO_RESULT_H
#define AIO_RESULT_H

typedef struct AIOIntResult {
    int *acc;
    char *rest;
} AIOIntResult;

void createAIOIntResult(AIOIntResult** result, int acc, char* rest);

typedef struct AIODouResult {
    double *acc;
    char *rest;
} AIODouResult;

void createAIODouResult(AIODouResult** result, double acc, char* rest);

typedef struct AIOChaResult {
    char *acc;
    char *rest;
} AIOChaResult;

void createAIOChaResult(AIOChaResult** result, char acc, char* rest);

typedef struct AIOStrResult {
    char *acc;
    char *rest;
} AIOStrResult;

void createAIOStrResult(AIOStrResult** result, char* acc, char* rest);

#endif //AIO_RESULT_H