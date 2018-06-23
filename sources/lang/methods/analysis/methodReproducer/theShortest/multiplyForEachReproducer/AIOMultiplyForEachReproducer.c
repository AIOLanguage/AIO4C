#include "../../../../../../../headers/lib/collections/maps/AIOVariableMap.h"
#include "../../../../../../../headers/lang/methods/bundle/AIOBundle.h"
#include "../../../../../../../headers/lang/methods/AIOMethodContainer.h"
#include "../../../../../../../headers/lang/methods/analysis/methodReproducer/theShortest/AIOTheShortestReproducer.h"

aioInt multiplyInt(aioInt first, aioInt second) {
    return first * second;
}

aioDou multiplyDou(aioDou first, aioDou second) {
    return first * second;
}

int intMultiplyForEachTypeOperationReproduce(AIOVariableMap *argMap, AIOBundle *bundle) {
    intOperationForEachTypeOperationReproduce(argMap, bundle, multiplyInt);
}

int douMultiplyForEachTypeOperationReproduce(AIOVariableMap *argMap, AIOBundle *bundle) {
    return douOperationForEachTypeOperationReproduce(argMap, bundle, multiplyDou);
}

void multiplyForEachReproduce(AIOVariableMap *argMap, AIOBundle *bundle) {
    if (argMap->size != 0) {
        if (intMultiplyForEachTypeOperationReproduce(argMap, bundle) == 1) {
            return;
        }
        if (douMultiplyForEachTypeOperationReproduce(argMap, bundle) == 1) {
            return;
        }
        // 아마있을거야 long 또는 float =)
    }
}