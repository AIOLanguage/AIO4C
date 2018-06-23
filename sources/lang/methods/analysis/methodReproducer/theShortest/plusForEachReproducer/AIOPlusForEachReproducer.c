#include "../../../../../../../headers/lib/collections/maps/AIOVariableMap.h"
#include "../../../../../../../headers/lang/methods/bundle/AIOBundle.h"
#include "../../../../../../../headers/lang/methods/AIOMethodContainer.h"
#include "../../../../../../../headers/lang/methods/analysis/methodReproducer/theShortest/AIOTheShortestReproducer.h"

AIOInt plusInt(AIOInt first, AIOInt second) {
    return first + second;
}

AIODou plusDou(AIODou first, AIODou second) {
    return first + second;
}

int intPlusForEachTypeOperationReproduce(AIOVariableMap *argMap, AIOBundle *bundle) {
    intOperationForEachTypeOperationReproduce(argMap, bundle, plusInt);
}

int douPlusForEachTypeOperationReproduce(AIOVariableMap *argMap, AIOBundle *bundle) {
    return douOperationForEachTypeOperationReproduce(argMap, bundle, plusDou);
}

void plusForEachReproduce(AIOVariableMap *argMap, AIOBundle *bundle) {
    if (argMap->size != 0) {
        if (intPlusForEachTypeOperationReproduce(argMap, bundle) == 0) {
            return;
        }
        if (douPlusForEachTypeOperationReproduce(argMap, bundle) == 0) {
            return;
        }
        // 아마있을거야 long 또는 float =)
    }
}