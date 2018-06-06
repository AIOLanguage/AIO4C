#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../headers/lang/object/objectManager/AIOObjectManager.h"
#include "../../headers/lang/methods/variable/AIOVariable.h"

AIOObjectManager* aioObjectManager;

int main(){
    AIOVariable* aioVariable;
    enum AIOType aioType = AIO_DOU;
    createAIOVariable(&aioVariable, "a", "1234567.0", 0, &aioType);
    return 0;
}