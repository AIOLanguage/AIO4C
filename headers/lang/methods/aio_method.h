#include "methodDefinition/aio_method_definition.h"
#include "bundle/aio_bundle.h"
#include "../../lib/collections/maps/AIOVariableMap.h"
#include "analysis/methodReproducer/aio_method_reproducer.h"
#include "AIOMethodContainer.h"
#include "../object/AIOObject.h"
#include "../../reservedNames/AIOReservedNamesContainer.h"

#ifndef AIO_METHOD_H

typedef struct aio_method {
    aio_method_container *methodContainer;
} aio_method;

aio_object *new_aio_method_and_invoke(aio_method **method, aio_method_definition *method_definition,
                                      aio_bundle *bundle);

int contains_variable(char *variable_name, aio_method_container *method_container);

int contains_variable_in_map(const char *variable_name, const aio_variable_map *variable_map);

void set_variable(aio_variable *variable, aio_method_container *method_container);

#endif //AIO_METHOD_H