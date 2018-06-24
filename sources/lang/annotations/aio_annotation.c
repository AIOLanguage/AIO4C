#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../headers/lang/annotations/aio_annotation.h"

//Passed JUnitTest!
aio_annotation *new_aio_annotation(char *methodName, char *annotationType) {
    //Create annotation:
    aio_annotation *annotation = calloc(1, sizeof(aio_annotation));
    if (annotation == NULL) {
        perror("cannot allocate memory for aio_annotation");
        exit(1);
    }
    //Set annotation name:
    annotation->methodName = methodName;
    //Set annotation type:
    annotation->annotationType = annotationType;
    return annotation;
}