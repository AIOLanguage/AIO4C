#ifndef AIO_METHOD_DEFINITION_BUILDER_H
#define AIO_METHOD_DEFINITION_BUILDER_H

#include "aio_method_definition.h"

aio_method_definition *build_aio_method_definition(char *method_name, string_list *source_code, int start_index);

int is_the_shortest_in_the_same_object(const char *operation);

int is_the_shortest_in_the_other_object(const char *operation);

#endif //AIO_METHOD_DEFINITION_BUILDER_H