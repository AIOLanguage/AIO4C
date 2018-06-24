#ifndef AIO_ANNOTATION_H
#define AIO_ANNOTATION_H

typedef struct aio_annotation {
    char *methodName;
    char *annotationType;
} aio_annotation;

aio_annotation* new_aio_annotation(char *methodName, char *annotationType);

#endif //AIO_ANNOTATION_H