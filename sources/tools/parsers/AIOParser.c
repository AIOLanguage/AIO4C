#include <stdio.h>
#include "../../../headers/lang/types/AIOType.h"
#include "../../../headers/lang/object/AIOObject.h"
#include "../../../headers/lang/methods/AIOMethodContainer.h"
#include "../../../headers/lang/methods/AIOMethod.h"
#include "../../../headers/tools/parsers/AIOParser.h"

aio_str
parse_line_expression(aio_object *object, aio_method_definition *methodDefinition,
                      aio_method_container *methodContainer,
                      char *codeLine) {
    char *result;
    //첫 단어는 "int"입니다.
    result = parseIntLineExpression(object, methodDefinition, methodContainer, codeLine);
    //첫 단어는 "dou"입니다.
    result = parseDouLineExpression(object, methodDefinition, methodContainer, codeLine);
    //첫 단어는 "dou"입니다.
    result = parseChaLineExpression(object, methodDefinition, methodContainer, codeLine);
    //첫 단어는 "dou"입니다.
    result = parseStrLineExpression(object, methodDefinition, methodContainer, codeLine);
}

AIOVariable *getVariable(char *variableName, aio_method_container *methodContainer) {
    if (containsVariableInMap(variableName, methodContainer->argMap) == 0) {
        return getAIOVariableInMapByName(methodContainer->argMap, variableName);
    }
    if (containsVariableInMap(variableName, methodContainer->variableMap) == 0) {
        return getAIOVariableInMapByName(methodContainer->variableMap, variableName);
    }
    perror("error: try get not exist variable!");
}