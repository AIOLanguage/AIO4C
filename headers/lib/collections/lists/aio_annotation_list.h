#ifndef AIO_ANNOTATION_LIST_H
#define AIO_ANNOTATION_LIST_H

#include "../../../lang/annotations/aio_annotation.h"

typedef struct aio_annotation_list {
    int capacity;
    int size;
    aio_annotation **annotations;
} aio_annotation_list;

aio_annotation_list *new_annotation_list();

void add_in_annotation_list(aio_annotation_list *annotation_list, aio_annotation *annotation);

aio_annotation *get_annotation_in_list_by_index(aio_annotation_list *annotation_list, int index);

#endif //AIO_ANNOTATION_LIST_H