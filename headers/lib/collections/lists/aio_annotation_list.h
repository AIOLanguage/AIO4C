#ifndef AIO_ANNOTATION_LIST_H
#define AIO_ANNOTATION_LIST_H

#include "../../../lang/aio_annotation/aio_annotation.h"

typedef struct aio_annotation_list {
    int capacity;
    int size;
    aio_annotation **annotations;
} aio_annotation_list;

aio_annotation_list *new_annotation_list();

void add_annotation_in_list(aio_annotation_list *annotation_list, aio_annotation *annotation);

void delete_annotation_list(aio_annotation_list *annotation_list);

#endif //AIO_ANNOTATION_LIST_H