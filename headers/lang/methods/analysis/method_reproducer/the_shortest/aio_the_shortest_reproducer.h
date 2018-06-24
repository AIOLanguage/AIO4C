#ifndef AIO_THE_SHORTEST_REPRODUCER_H
#define AIO_THE_SHORTEST_REPRODUCER_H

#include "../../../../object/aio_object.h"

void reproduceTheShortestMethod(aio_object *object, aio_method_definition *method_definition,
                                aio_method_container *method_container, aio_bundle *bundle);

int
int_operation_for_each_type_operation_reproduce(aio_variable_map *arg_map, aio_bundle *bundle,
                                                aio_int (apply)(aio_int, aio_int));

int
dou_operation_for_each_type_operation_reproduce(aio_variable_map *arg_map, aio_bundle *bundle,
                                                aio_dou (apply)(aio_dou, aio_dou));

#endif //AIO_THE_SHORTEST_REPRODUCER_H