#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/collections/lists/AIOAnnotationList.h"

//Passed JUnitTest!
void createAnnotationList(AIOAnnotationList **annotationList) {
    //Create the same mutable list:
    *annotationList = calloc(1, sizeof(AIOAnnotationList));
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
    (*annotationList)->annotations = calloc(2, sizeof(AIOAnnotation *));
    if ((*annotationList)->annotations == NULL) {
        perror("can not allocate memory for annotations in aio annotation list");
        exit(1);
    }
}

//Passed JUnitTest!
void updateMemoryInMutableListOfAnnotations(AIOAnnotationList *listOfAnnotations) {
    if (*listOfAnnotations->size + 1 == *listOfAnnotations->capacity) {
        *listOfAnnotations->capacity = *listOfAnnotations->capacity * 2;
        listOfAnnotations->annotations = realloc(listOfAnnotations->annotations,
                                                 *listOfAnnotations->capacity * sizeof(AIOAnnotation));
    }
}

//Passed JUnitTests!
void addInAnnotationList(AIOAnnotationList *listOfAnnotations, AIOAnnotation *annotation) {
    //Check to update capacity:
    updateMemoryInMutableListOfAnnotations(listOfAnnotations);
    //Set annotation:
    listOfAnnotations->annotations[*listOfAnnotations->size] = annotation;
    *listOfAnnotations->size = *listOfAnnotations->size + 1;
}

//Passed JUnitTests!
AIOAnnotation *getAnnotationInListByIndex(AIOAnnotationList *listOfAnnotations, int index) {
    if (index < 0 || *listOfAnnotations->size <= index) {
        perror("Cannot get index: %d in MutableList");
        exit(1);
    } else {
        return listOfAnnotations->annotations[index];
    }
}