#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lib/collections/lists/aio_annotation_list.h"
#include "../../../../headers/lib/utils/error_utils/error_utils.h"

//Passed JUnitTest!
aio_annotation_list *new_annotation_list() {
    aio_annotation_list *annotation_list = calloc(1, sizeof(aio_annotation_list));
    annotation_list->capacity = 2;
    annotation_list->size = 0;
    annotation_list->annotations = calloc(2, sizeof(aio_annotation *));
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
void add_annotation_in_list(aio_annotation_list *annotation_list, aio_annotation *annotation) {
    //Check from update capacity:
    update_memory_in_mutable_annotation_list(annotation_list);
    //Set annotation:
    annotation_list->annotations[annotation_list->size] = annotation;
    annotation_list->size++;
}

//Passed JUnitTests!
aio_annotation *get_annotation_in_list_by_index(aio_annotation_list *annotation_list, int index) {
    if (index < 0 || annotation_list->size <= index) {
        throw_error("Cannot from index in annotation list!");
    } else {
        return annotation_list->annotations[index];
    }
}