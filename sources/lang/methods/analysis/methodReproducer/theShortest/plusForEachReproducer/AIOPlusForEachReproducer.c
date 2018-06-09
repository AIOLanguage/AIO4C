#include "../../../../../../../headers/lang/object/AIOObject.h"
#include "../../../../../../../headers/lib/utils/stringUtils/StringUtils.h"
#include "../../../../../../../headers/lang/methods/AIOMethodContainer.h"
#include "../../../../../../../headers/lang/methods/analysis/methodReproducer/theShortest/AIOAbstractForEachOperationReproducer.h"

void douPlusForEachTypeOperationReproduce() {

}

void apply(void **result, void *value) {
    **((int **) result) = **((int **) result) + *((int *) value);
}
//
//void intPlusForEachTypeOperationReproduce(AIOObject *object, AIOMethodDefinition *methodDefinition,
//                                          AIOMethodContainer *methodContainer, AIOBundle *bundle) {
//    reproduceForEachOperation(methodContainer->variableMap, bundle, isAIOIntType, matchesInt, toInt, apply, intToString);
//}

void plusForEachReproduce(AIOObject *object, AIOMethodDefinition *methodDefinition,
                          AIOMethodContainer *methodContainer, AIOBundle *bundle) {
//    if (*argMap->size != 0) {
//       intPlusForEachTypeOperationReproduce();
//        douPlusForEachTypeOperationReproduce();
//    }
}