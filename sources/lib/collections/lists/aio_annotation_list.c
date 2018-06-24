#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/collections/lists/aio_annotation_list.h"

//Passed JUnitTest!
void new_annotation_list(aio_annotation_list **annotationList) {
    //Create the same mutable list:
    *annotationList = calloc(1, sizeof(aio_annotation_list));
    if (*annotationList == NULL) {
        perror("can not allocate memory for aio annotation list");
        exit(1);
    }
    //Create capacity:
    (*annotationList)->capacity = calloc(1, sizeof(int));
    if ((*annotationList)->capacity == NULL) {
        perror("can not allocate memory for capacity in aio annotation list");
        exit(1);
    }
    *(*annotationList)->capacity = 2;
    //Create size:
    (*annotationList)->size = calloc(1, sizeof(int));
    if ((*annotationList)->size == NULL) {
        perror("can not allocate memory for size in aio annotation list");
        exit(1);
    }
    *(*annotationList)->size = 0;
    //Create char capacity that equals 2:
    (*annotationList)->annotations = calloc(2, sizeof(aio_annotation *));
    if ((*annotationList)->annotations == NULL) {
        perror("can not allocate memory for annotations in aio annotation list");
        exit(1);
    }
}

//Passed JUnitTest!
void updateMemoryInMutableListOfAnnotations(aio_annotation_list *listOfAnnotations) {
    if (*listOfAnnotations->size + 1 == *listOfAnnotations->capacity) {
        *listOfAnnotations->capacity = *listOfAnnotations->capacity * 2;
        listOfAnnotations->annotations = realloc(listOfAnnotations->annotations,
                                                 *listOfAnnotations->capacity * sizeof(aio_annotation));
    }
}

//Passed JUnitTests!
void add_in_annotation_list(aio_annotation_list *annotation_list, aio_annotation *annotation) {
    //Check to update capacity:
    updateMemoryInMutableListOfAnnotations(annotation_list);
    //Set annotation:
    annotation_list->annotations[*annotation_list->size] = annotation;
    *annotation_list->size = *annotation_list->size + 1;
}

//Passed JUnitTests!
aio_annotation *get_annotation_in_list_by_index(aio_annotation_list *annotation_list, int index) {
    if (index < 0 || *annotation_list->size <= index) {
        perror("Cannot get index: %d in MutableList");
        exit(1);
    } else {
        return annotation_list->annotations[index];
    }
}