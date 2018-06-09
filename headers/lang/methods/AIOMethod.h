#include "methodDefinition/AIOMethodDefinition.h"
#include "bundle/AIOBundle.h"
#include "../../lib/collections/maps/AIOVariableMap.h"
#include "analysis/methodReproducer/AIOMethodReproducer.h"
#include "AIOMethodContainer.h"
#include "../object/AIOObject.h"

#ifndef AIO_METHOD_H

typedef struct AIOMethod {
    AIOMethodContainer *methodContainer;
    AIOMethodReproducer *methodReproducer;
} AIOMethod;


void createAIOMethodAndInvoke(AIOObject* object, AIOMethod **method, AIOMethodDefinition *methodDefinition
        , AIOBundle *bundle);

#endif //AIO_METHOD_H