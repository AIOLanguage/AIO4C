#include <malloc.h>
#include <mem.h>
#include "../../../../../../../headers/lib/collections/maps/AIOVariableMap.h"
#include "../../../../../../../headers/lang/methods/bundle/AIOBundle.h"

void concatForEachReproduce(AIOVariableMap *argMap, AIOBundle *bundle) {
    if (*(argMap->variables[0]->type) == AIO_STR) {
        size_t length = 0;
        //카운트 길이:
        for (int i = 0; i < *argMap->size; ++i) {
            length = length + strlen(argMap->variables[i]->value);
        }
        aioStr result = calloc(length + 1, sizeof(char));
        strcpy(result, argMap->variables[0]->value);
        for (int i = 1; i < *argMap->size; ++i) {
            strcat(result, argMap->variables[i]->value);
        }
        addInListOfString(bundle->outputValues, result);
    }
}