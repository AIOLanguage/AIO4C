#include <malloc.h>
#include "../../declarations/aio_declaration.h"
#include "../../annotations/aio_annotation.h"
#include "aio_method_size_type.h"
#include "../../../lib/collections/lists/AIOAnnotationList.h"
#include "../../../lib/collections/lists/string_list.h"

#ifndef AIO_METHOD_DEFINITION_H
#define AIO_METHOD_DEFINITION_H

typedef struct aio_method_definition {
    char *name;
    aio_declaration *declaration;
    aio_annotation_list *annotations;
    string_list *source_code;
    enum aio_method_size_type method_size_type;
} aio_method_definition;

aio_method_definition *new_aio_method_definition(char *name, aio_declaration *declaration,
                                                 aio_annotation_list *annotations, string_list *source_code,
                                                 enum aio_method_size_type method_size_type);

#endif //AIO_METHOD_DEFINITION_H