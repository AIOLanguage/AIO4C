#ifndef AIO_ANNOTATION_LIST_H
#define AIO_ANNOTATION_LIST_H

#include "../../../lang/annotations/AIOAnnotation.h"

typedef struct AIOAnnotationList {
    int* capacity;
    int* size;
    AIOAnnotation** annotations;
} AIOAnnotationList;

void createAnnotationList(AIOAnnotationList **listOfString);

void addInAnnotationList(AIOAnnotationList *listOfAnnotations, AIOAnnotation *annotation);

AIOAnnotation* getAnnotationInListByIndex(AIOAnnotationList *listOfAnnotations, int index);

#endif //AIO_ANNOTATION_LIST_H