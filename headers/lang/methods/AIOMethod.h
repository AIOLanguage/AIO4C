#include "methodDefinition/AIOMethodDefinition.h"
#include "bundle/AIOBundle.h"
#include "../../lib/collections/maps/AIOVariableMap.h"
#include "analysis/methodReproducer/AIOMethodReproducer.h"
#include "AIOMethodContainer.h"
#include "../object/AIOObject.h"
#include "../../reservedNames/AIOReservedNamesContainer.h"

#ifndef AIO_METHOD_H

typedef struct AIOMethod {
    AIOMethodContainer *methodContainer;
} AIOMethod;

void createAIOMethodAndInvoke(AIOObject *object, AIOMethod **method, AIOMethodDefinition *methodDefinition,
                              AIOBundle *bundle);

int containsVariable(char *variableName, AIOMethodContainer *methodContainer);

int containsVariableInMap(const char *variableName, const AIOVariableMap *variableMap);

void setVariable(AIOVariable* variable, AIOMethodContainer* methodContainer);

#endif //AIO_METHOD_H