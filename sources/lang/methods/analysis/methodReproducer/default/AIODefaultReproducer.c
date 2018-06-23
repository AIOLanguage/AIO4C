#include <stdio.h>
#include "../../../../../../headers/lang/object/AIOObject.h"
#include "../../../../../../headers/lang/methods/AIOMethodContainer.h"
#include "../../../../../../headers/lib/utils/stringUtils/string_utils.h"
#include "../../../../../../headers/lang/methods/analysis/methodReproducer/short/AIOShortReproducer.h"

void
reproduceDefaultMethod(AIOObject *object, AIOMethodDefinition *methodDefinition, AIOMethodContainer *methodContainer,
                       AIOBundle *bundle, char *codeLine) {
    printf("Default reproducing... %s", methodDefinition->name);
    StringList *sourceCode = methodDefinition->sourceCode;
    for (int i = 0; i < *sourceCode->size; ++i) {
        char *cleanLine;
//        trim(sourceCode->strings[i], &cleanLine);
        //variableCreator:
        // if (wasCreatingVariable == 0){
        //      continue;
        // }
        if (starts_with_prefix(sourceCode->strings[i], ">>") == 0) {
            reproduceShortMethod(object, methodDefinition, methodContainer, bundle, codeLine);
            break;
        }
    }
}