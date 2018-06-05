#ifndef AIO_ANNOTATION_H
#define AIO_ANNOTATION_H

typedef struct AIOAnnotation {
    char *methodName;
    char *annotationType;
} AIOAnnotation;

void createAIOAnnotation(AIOAnnotation** annotation, char* methodName, char* annotationType);

#endif //AIO_ANNOTATION_H