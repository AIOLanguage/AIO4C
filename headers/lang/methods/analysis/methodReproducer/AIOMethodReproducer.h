#ifndef AIO_METHOD_REPRODUCER_H
#define AIO_METHOD_REPRODUCER_H

#include "../../methodDefinition/AIOMethodDefinition.h"
#include "../../bundle/AIOBundle.h"
#include "../../AIOMethodContainer.h"

typedef struct AIOTheShortestReproducer {

} AIOTheShortestReproducer;

typedef struct AIOShortReproducer {

} AIOShortReproducer;

typedef struct AIODefaultReproducer {

} AIODefaultReproducer;

typedef struct AIOMethodReproducer {
    AIOTheShortestReproducer *shortestReproducer;
    AIOShortReproducer *shortReproducer;
    AIODefaultReproducer *defaultReproducer;
} AIOMethodReproducer;


void createAIOMethodReproducer(AIOMethodReproducer **methodReproducer, AIOMethodDefinition *methodDefinition,
                               AIOMethodContainer *container, AIOBundle *bundle);

void reproduceMethod(AIOMethodReproducer *methodReproducer);

#endif //AIO_METHOD_REPRODUCER_H