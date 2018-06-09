#include "methodDefinition/AIOMethodDefinition.h"
#include "bundle/AIOBundle.h"
#include "../../lib/collections/maps/AIOVariableMap.h"
#include "analysis/methodReproducer/AIOMethodReproducer.h"
#include "AIOMethodContainer.h"

#ifndef AIO_METHOD_H

typedef struct AIOMethod {
    AIOMethodContainer *methodContainer;
    AIOMethodReproducer *methodReproducer;
} AIOMethod;

#endif //AIO_METHOD_H

void createAIOMethod(AIOMethod **method, AIOMethodDefinition *methodDefinition, AIOBundle *bundle);

void invokeAIOMethod(AIOMethod *method);