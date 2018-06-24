#include "bundle/aio_bundle.h"
#include "../../lib/collections/maps/aio_variable_map.h"
#include "aio_method_container.h"
#include "../object/aio_object.h"

#ifndef AIO_METHOD_H

typedef struct aio_method {
    aio_method_container *methodContainer;
} aio_method;

void invoke_new_aio_method(aio_object *object, aio_method_definition *method_definition, aio_bundle *bundle);

int contains_variable(char *variable_name, aio_method_container *method_container);

int contains_variable_in_map(const char *variable_name, const aio_variable_map *variable_map);

void set_variable(aio_variable *variable, aio_method_container *method_container);

#endif //AIO_METHOD_H