#ifndef AIO_AIO_OBJECT_H
#define AIO_AIO_OBJECT_H

typedef struct AIOObject {
    char name[256];
    char folderName[256];
    struct AIOObjectFileLoader* loader;
} AIOObject;

typedef struct AIOObjectFileLoader {
    char sourceCode[1024][1024];
} AIOObjectFileLoader;

#endif //AIO_AIO_OBJECT_H