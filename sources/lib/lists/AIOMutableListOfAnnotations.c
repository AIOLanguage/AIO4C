#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../headers/lib/lists/AIOMutableListOfAnnotations.h"

void createMutableListOfAnnotations(AIOMutableListOfAnnotations **listOfAnnotations) {
    *listOfAnnotations = (AIOMutableListOfAnnotations *) calloc(1, sizeof(AIOMutableListOfAnnotations));
    *(*listOfAnnotations)->size = 0;
}

//Passed JUnitTests!
void addInMutableListOfAnnotations(AIOMutableListOfAnnotations *listOfAnnotations, AIOAnnotation* annotation) {
    listOfAnnotations->annotations[*listOfAnnotations->size] = annotation;
    listOfAnnotations->size++;
}

//Passed JUnitTests!
AIOAnnotation *getAnnotationInMutableListByIndex(AIOMutableListOfAnnotations *listOfAnnotations, int index) {
    if (index < 0 || *listOfAnnotations->size < index) {
        printf("Cannot get index: %d in MutableList", index);
        exit(1);
    } else {
        return listOfAnnotations->annotations[index];
    }
}