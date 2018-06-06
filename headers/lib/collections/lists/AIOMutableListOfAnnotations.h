#ifndef AIO_AIO_MUTABLE_LIST_OF_ANNOTATIONS_H
#define AIO_AIO_MUTABLE_LIST_OF_ANNOTATIONS_H

#include "../../../lang/annotations/AIOAnnotation.h"

typedef struct AIOMutableListOfAnnotations {
    int* capacity;
    int* size;
    AIOAnnotation** annotations;
} AIOMutableListOfAnnotations;

void createMutableListOfAnnotations(AIOMutableListOfAnnotations** listOfString);

void addInMutableListOfAnnotations(AIOMutableListOfAnnotations* listOfAnnotations, AIOAnnotation* annotation);

AIOAnnotation* getAnnotationInMutableListByIndex(AIOMutableListOfAnnotations *listOfAnnotations, int index);

#endif //AIO_AIO_MUTABLE_LIST_OF_ANNOTATIONS_H
