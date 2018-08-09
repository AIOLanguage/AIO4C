#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../headers/lang/aio_annotation/aio_annotation.h"

aio_annotation *new_aio_annotation(string name) {
    aio_annotation *annotation = calloc(1, sizeof(aio_annotation));
    annotation->name = name;
    return annotation;
}

void free_aio_annotation(aio_annotation *annotation) {
    free(annotation);
}