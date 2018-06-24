#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/collections/lists/aio_annotation_list.h"

//Passed JUnitTest!
aio_annotation_list *new_annotation_list() {
    //Create the same mutable list:
    aio_annotation_list *annotation_list = calloc(1, sizeof(aio_annotation_list));
    if (annotation_list == NULL) {
        perror("can not allocate memory for aio annotation list");
        exit(1);
    }
    //Create capacity:
    annotation_list->capacity = 2;
    //Create size:
    annotation_list->size = 0;
    //Create char capacity that equals 2:
    annotation_list->annotations = calloc(2, sizeof(aio_annotation *));
    if (annotation_list->annotations == NULL) {
        perror("can not allocate memory for annotations in aio annotation list");
        exit(1);
    }
    return annotation_list;
}

//Passed JUnitTest!
void update_memory_in_mutable_annotation_list(aio_annotation_list *annotation_list) {
    if (annotation_list->size + 1 == annotation_list->capacity) {
        annotation_list->capacity = annotation_list->capacity * 2;
        annotation_list->annotations = realloc(annotation_list->annotations,
                                               annotation_list->capacity * sizeof(aio_annotation));
    }
}

//Passed JUnitTests!
void add_in_annotation_list(aio_annotation_list *annotation_list, aio_annotation *annotation) {
    //Check to update capacity:
    update_memory_in_mutable_annotation_list(annotation_list);
    //Set annotation:
    annotation_list->annotations[annotation_list->size] = annotation;
    annotation_list->size++;
}

//Passed JUnitTests!
aio_annotation *get_annotation_in_list_by_index(aio_annotation_list *annotation_list, int index) {
    if (index < 0 || annotation_list->size <= index) {
        perror("Cannot get index: %d in MutableList");
        exit(1);
    } else {
        return annotation_list->annotations[index];
    }
}