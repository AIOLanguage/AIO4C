#include "methodDefinition/aio_method_definition.h"
#include "bundle/aio_bundle.h"
#include "../../lib/collections/maps/AIOVariableMap.h"
#include "analysis/methodReproducer/aio_method_reproducer.h"
#include "AIOMethodContainer.h"
#include "../object/AIOObject.h"
#include "../../reservedNames/AIOReservedNamesContainer.h"

#ifndef AIO_METHOD_H

typedef struct AIOMethod {
    aio_method_container *methodContainer;
} AIOMethod;

void createAIOMethodAndInvoke(aio_object *object, AIOMethod **method, aio_method_definition *methodDefinition,
                              aio_bundle *bundle);

int containsVariable(char *variableName, aio_method_container *methodContainer);

int containsVariableInMap(const char *variableName, const aio_variable_map *variableMap);

void setVariable(AIOVariable* variable, aio_method_container* methodContainer);

#endif //AIO_METHOD_H