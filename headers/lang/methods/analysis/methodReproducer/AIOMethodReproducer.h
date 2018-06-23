#ifndef AIO_METHOD_REPRODUCER_H
#define AIO_METHOD_REPRODUCER_H

#include "../../methodDefinition/AIOMethodDefinition.h"
#include "../../bundle/AIOBundle.h"
#include "../../AIOMethodContainer.h"
#include "theShortest/AIOTheShortestReproducer.h"
#include "default/AIODefaultReproducer.h"
#include "short/AIOShortReproducer.h"
#include "../../../object/AIOObject.h"

void reproduceMethod(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer
        , AIOBundle *bundle);

#endif //AIO_METHOD_REPRODUCER_H