#include "methodDefinition/AIOMethodDefinition.h"
#include "bundle/AIOBundle.h"
#include "analysis/methodReproducer/AIOMethodReproducer.h"
#include "../../lib/collections/maps/AIOVariableMap.h"

#ifndef AIO_METHOD_H

typedef struct AIOMethodContainer {
    AIOVariableMap* argMap;
    AIOVariableMap* variableMap;
} AIOMethodContainer;

typedef struct AIOMethod {
    AIOMethodContainer* methodContainer;
    AIOMethodReproducer* methodReproducer;
} AIOMethod;

#endif //AIO_METHOD_H

void createAIOMethod(AIOMethod **method, AIOMethodDefinition *methodDefinition, AIOBundle *bundle);

void invokeAIOMethod(AIOMethod *method);