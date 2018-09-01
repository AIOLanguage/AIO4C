#include <malloc.h>
#include <lang/aio_annotation/aio_annotation.h>
#include <lib/utils/memory_utils/memory_utils.h>
#include <lib/utils/str_hook/str_hook_utils/str_hook_utils.h>
#include <lib/utils/str_hook/str_hook.h>

#define AIO_ANNOTATION_DEBUG

#define AIO_ANNOTATION_TAG "AIO_ANNOTATION"

#define INIT_SIZE 0

#define INIT_CAPACITY 2

/**
 * Annotation.
 **/

const_aio_annotation *new_aio_annotation(const_str_hook *name)
{
    aio_annotation *annotation = new_object(sizeof(aio_annotation));
    annotation->name = new_str_hook_by_other(name);
    return annotation;
}

void free_aio_annotation(const_aio_annotation *annotation)
{
    free_const_str_hook(annotation->name);
    free((void *) annotation);
}

/**
 * List
 */

aio_annotation_list *new_aio_annotation_list()
{
    aio_annotation_list *list = new_object(sizeof(aio_annotation_list));
    list->capacity = INIT_CAPACITY;
    list->size = INIT_SIZE;
    list->annotations = new_object_array(INIT_CAPACITY, sizeof(aio_annotation *));
    return list;
}

static void update_memory_in_aio_annotation_list(aio_annotation_list *list)
{
    if (list->size == list->capacity) {
        list->capacity *= INIT_CAPACITY;
        list->annotations = reallocate_object_array(
                list->annotations,
                list->capacity,
                sizeof(aio_annotation *)
        );
    }
}

void add_aio_annotation_in_list(aio_annotation_list *annotation_list, const_aio_annotation *annotation)
{
    update_memory_in_aio_annotation_list(annotation_list);
    annotation_list->annotations[annotation_list->size] = annotation;
    annotation_list->size++;
}