#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../headers/lang/aio_annotation/aio_annotation.h"

aio_annotation *new_aio_annotation(const_string methodName, const_string annotationType) {
    aio_annotation *annotation = calloc(1, sizeof(aio_annotation));
    annotation->method_name = methodName;
    annotation->annotation_type = annotationType;
    return annotation;
}

void delete_aio_annotation(aio_annotation *annotation) {

}