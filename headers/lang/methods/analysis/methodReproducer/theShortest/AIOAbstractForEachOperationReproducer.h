#ifndef AIO_ABSTRACT_FOR_EACH_OPERATION_REPRODUCER_H
#define AIO_ABSTRACT_FOR_EACH_OPERATION_REPRODUCER_H


#include "../../../AIOMethodContainer.h"
#include "../../../bundle/AIOBundle.h"

void reproduceForEachOperation(AIOVariableMap *argMap, AIOBundle *bundle,
                               int (equalsType)(enum AIOType variableType),
                               int (matchesType)(char *),
                               void (toType)(char *src, void **dst),
                               void (apply)(void **result, void *value),
                               void (toString)(void *src, char **dst));

#endif //AIO_ABSTRACT_FOR_EACH_OPERATION_REPRODUCER_H