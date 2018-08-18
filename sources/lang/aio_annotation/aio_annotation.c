#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../headers/lang/aio_annotation/aio_annotation.h"
#include "../../../headers/lib/utils/memory_utils/memory_utils.h"
#include "../../../headers/lib/utils/string_hook/string_hook_utils/str_hook_utils.h"
#include "../../../headers/lib/utils/error_utils/error_utils.h"

#define AIO_ANNOTATION_TAG "AIO_ANNOTATION"

/**
 * Annotation.
 */

const_aio_annotation *new_aio_annotation(const_str_hook *name) {
    aio_annotation *annotation = new_object(sizeof(aio_annotation));
    annotation->name = new_str_hook_by_other_hook(name);
    return annotation;
}

void free_aio_annotation(const_aio_annotation *annotation) {
    free_const_str_hook(annotation->name);
    free((void *) annotation);
}

/**
 * List
 */

aio_annotation_list *new_aio_annotation_list() {
    aio_annotation_list *list = new_object(sizeof(aio_annotation_list));
    list->capacity = 2;
    list->size = 0;
    list->annotations = new_object_array(2, sizeof(aio_annotation *));
    return list;
}

void update_memory_in_aio_annotation_list(aio_annotation_list *list) {
    if (list->size + 1 == list->capacity) {
        list->capacity = list->capacity * 2;
        list->annotations = realloc(list->annotations, list->capacity * sizeof(aio_annotation *));
    }
}

void add_aio_annotation_in_list(aio_annotation_list *annotation_list, const_aio_annotation *annotation) {
    update_memory_in_aio_annotation_list(annotation_list);
    annotation_list->annotations[annotation_list->size] = annotation;
    annotation_list->size++;
}