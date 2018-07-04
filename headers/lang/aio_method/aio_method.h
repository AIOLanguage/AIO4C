#include "bundle/aio_bundle.h"
#include "../../lib/collections/maps/aio_variable_map.h"
#include "aio_method_container.h"
#include "../object/aio_file.h"

#ifndef AIO_METHOD_H

typedef struct aio_method {
    aio_method_container *method_container;
} aio_method;

void invoke_new_aio_method(aio_file *object, aio_method_definition *method_definition, aio_bundle *bundle);

boolean contains_variable(const_string variable_name, aio_method_container *method_container);

boolean contains_variable_in_map(const_string variable_name, aio_variable_map *variable_map);

void set_variable(aio_variable *variable, aio_method_container *method_container);

#endif //AIO_METHOD_H