#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/collections/lists/AIOMutableListOfAnnotations.h"

//Passed JUnitTest!
void createMutableListOfAnnotations(AIOMutableListOfAnnotations **listOfAnnotations) {
    //Create the same mutable list:
    *listOfAnnotations = malloc(sizeof(AIOMutableListOfAnnotations));
    //Create capacity:
    (*listOfAnnotations)->capacity = malloc(sizeof(int));
    *(*listOfAnnotations)->capacity = 2;
    //Create size:
    (*listOfAnnotations)->size = malloc(sizeof(int));
    *(*listOfAnnotations)->size = 0;
    //Create char capacity that equals 2:
    (*listOfAnnotations)->annotations = malloc(2 * sizeof(AIOAnnotation));
}

//Passed JUnitTest!
void updateMemoryInMutableListOfAnnotations(AIOMutableListOfAnnotations *listOfAnnotations) {
    if (*listOfAnnotations->size + 1 == *listOfAnnotations->capacity) {
        *listOfAnnotations->capacity = *listOfAnnotations->capacity * 2;
        listOfAnnotations->annotations = realloc(listOfAnnotations->annotations,
                                                 *listOfAnnotations->capacity * sizeof(AIOAnnotation));
    }
}

//Passed JUnitTests!
void addInMutableListOfAnnotations(AIOMutableListOfAnnotations *listOfAnnotations, AIOAnnotation *annotation) {
    //Check to update capacity:
    updateMemoryInMutableListOfAnnotations(listOfAnnotations);
    //Set annotation:
    listOfAnnotations->annotations[*listOfAnnotations->size] = annotation;
    *listOfAnnotations->size = *listOfAnnotations->size + 1;
}

//Passed JUnitTests!
AIOAnnotation *getAnnotationInMutableListByIndex(AIOMutableListOfAnnotations *listOfAnnotations, int index) {
    if (index < 0 || *listOfAnnotations->size <= index) {
        perror("Cannot get index: %d in MutableList");
        exit(1);
    } else {
        return listOfAnnotations->annotations[index];
    }
}