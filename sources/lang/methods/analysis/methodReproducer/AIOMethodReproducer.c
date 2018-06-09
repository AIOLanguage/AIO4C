#include "../../../../../headers/lang/methods/bundle/AIOBundle.h"
#include "../../../../../headers/lang/methods/analysis/methodReproducer/AIOMethodReproducer.h"
#include "../../../../../headers/lib/utils/stringUtils/StringUtils.h"
#include "../../../../../headers/lib/utils/operationUtils/OperationUtils.h"
#include "../../../../../headers/lang/methods/analysis/methodReproducer/theShortest/plusForEachReproducer/AIOPlusForEachReproducer.h"
#include "../../../../../headers/lang/methods/analysis/methodReproducer/theShortest/multiplyForEachReproducer/AIOMultiplyForEachReproducer.h"
#include "../../../../../headers/lang/methods/analysis/methodReproducer/theShortest/concatForEachReproducer/AIOConcatForEachReproducer.h"
#include "../../../../../headers/lang/methods/methodDefinition/AIOMethodDefinitionBuilder.h"
#include "../../../../../headers/lang/object/AIOObject.h"
#include "../../../../../headers/lib/collections/maps/AIOObjectMap.h"
#include "../../../../../headers/lang/object/objectManager/AIOObjectManager.h"
#include "../../../../../headers/lib/utils/pathUtils/FileUtils.h"
#include <mem.h>
#include <stdio.h>
#include <process.h>

AIOObjectManager *aioObjectManager;



void shortReproduce(AIOShortReproducer *shortReproducer) {

}


void reproduceMethod(AIOObject* object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer
        , AIOBundle *bundle) {
    switch (methodDefinition->methodSizeType) {
        case THE_SHORTEST:
            reproduceTheShortestMethod(object, methodDefinition, methodContainer->variableMap, bundle);
            break;
        case SHORT:
            shortReproduce();
            break;
        case DEFAULT:
            defaultReproduce();
            break;
    }
}