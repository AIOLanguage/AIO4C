#include "../../../../../../headers/lib/collections/maps/AIOVariableMap.h"
#include "../../../../../../headers/lang/methods/AIOMethodContainer.h"
#include "../../../../../../headers/lang/methods/bundle/AIOBundle.h"

void reproduceForEachOperation(AIOVariableMap *argMap, AIOBundle *bundle,
                               int (equalsType)(enum AIOType variableType),
                               int (matchesType)(char *),
                               void (toType)(char *src, void **dst),
                               void (apply)(void **result, void *value),
                               void (toString)(void *src, char **dst)) {
    if (equalsType(*argMap->variables[0]->type) == 0) {
        void *result;
        toType(argMap->variables[0]->value, &result);
        for (int i = 1; i < *argMap->size; ++i) {
            if (matchesType(argMap->variables[i]->value) == 0) {
                void *argValue;
                toType(argMap->variables[i]->value, &argValue);
                apply(&result, argValue);
            }
        }
        char *outputResult;
        toString(result, &outputResult);
        addInListOfString(bundle->outputValues, outputResult);
    }
}