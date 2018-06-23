#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../../headers/lang/object/AIOObject.h"
#include "../../../../../headers/lang/methods/AIOMethodContainer.h"
#include "../../../../../headers/lang/methods/analysis/methodReproducer/theShortest/AIOTheShortestReproducer.h"
#include "../../../../../headers/lang/methods/analysis/methodReproducer/short/AIOShortReproducer.h"
#include "../../../../../headers/lang/methods/analysis/methodReproducer/default/AIODefaultReproducer.h"
#include "../../../../../headers/lang/methods/analysis/methodReproducer/AIOMethodReproducer.h"

void reproduceMethod(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
                     AIOBundle *bundle) {
    switch (methodDefinition->methodSizeType) {
        case THE_SHORTEST:
            reproduceTheShortestMethod(object, methodDefinition, methodContainer, bundle);
            break;
        case SHORT:
            reproduceShortMethod(object, methodDefinition, methodContainer, bundle);
            break;
        case DEFAULT:
            reproduceDefaultMethod(object, methodDefinition, methodContainer, bundle);
            break;
    }
}