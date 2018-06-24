#ifndef AIO_ANNOTATION_LIST_H
#define AIO_ANNOTATION_LIST_H

#include "../../../lang/annotations/aio_annotation.h"

typedef struct AIOAnnotationList {
    int* capacity;
    int* size;
    aio_annotation** annotations;
} aio_annotation_list;

void createAnnotationList(aio_annotation_list **annotationList);

void addInAnnotationList(aio_annotation_list *listOfAnnotations, aio_annotation *annotation);

aio_annotation* getAnnotationInListByIndex(aio_annotation_list *listOfAnnotations, int index);

#endif //AIO_ANNOTATION_LIST_H