#ifndef AIO_ANNOTATION_H
#define AIO_ANNOTATION_H

#include "../../lib/utils/string_utils/string_utils.h"
#include "../../lib/utils/str_hook/str_hook.h"

/**
 * Annotation.
 */

typedef struct aio_annotation {
    const struct str_hook *name;
} aio_annotation;

const struct aio_annotation *new_aio_annotation(const struct str_hook *name);

void free_aio_annotation(const struct aio_annotation *annotation);

/**
 * List.
 */

typedef struct aio_annotation_list {
    unsigned int capacity;
    unsigned int size;
    const struct aio_annotation **annotations;
} aio_annotation_list;

struct aio_annotation_list *new_aio_annotation_list();

void add_aio_annotation_in_list(struct aio_annotation_list *annotation_list, const struct aio_annotation *annotation);

void free_annotation_list(struct aio_annotation_list *annotation_list);

/**
 * Typedef utils.
 */

typedef const aio_annotation const_aio_annotation;

typedef const aio_annotation **const_aio_annotation_array;

typedef const aio_annotation_list const_aio_annotation_list;

#endif //AIO_ANNOTATION_H