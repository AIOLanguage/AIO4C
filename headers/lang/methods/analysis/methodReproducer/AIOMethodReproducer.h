#ifndef AIO_METHOD_REPRODUCER_H
#define AIO_METHOD_REPRODUCER_H

#include "../../methodDefinition/AIOMethodDefinition.h"
#include "../../bundle/AIOBundle.h"
#include "../../AIOMethodContainer.h"
#include "theShortest/AIOTheShortestReproducer.h"
#include "default/AIODefaultReproducer.h"
#include "short/AIOShortReproducer.h"

typedef struct AIOMethodReproducer {
    AIOMethodDefinition* methodDefinition;
    AIOMethodContainer* methodContainer;
    AIOBundle* bundle;
    AIOTheShortestReproducer *shortestReproducer;
    AIOShortReproducer *shortReproducer;
    AIODefaultReproducer *defaultReproducer;
} AIOMethodReproducer;


void createAIOMethodReproducer(AIOMethodReproducer **methodReproducer, AIOMethodDefinition *methodDefinition,
                               AIOMethodContainer *methodContainer, AIOBundle *bundle);

void reproduceMethod(AIOMethodReproducer* methodReproducer);

#endif //AIO_METHOD_REPRODUCER_H