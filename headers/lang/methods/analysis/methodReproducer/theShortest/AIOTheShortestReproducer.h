#ifndef AIO_THE_SHORTEST_REPRODUCER_H
#define AIO_THE_SHORTEST_REPRODUCER_H

#include "../../../../object/AIOObject.h"

void reproduceTheShortestMethod(AIOObject *object, AIOMethodDefinition *methodDefinition,
                                AIOMethodContainer *methodContainer, AIOBundle *bundle);

int
intOperationForEachTypeOperationReproduce(AIOVariableMap *argMap, AIOBundle *bundle, aioInt (apply)(aioInt, aioInt));

int
douOperationForEachTypeOperationReproduce(AIOVariableMap *argMap, AIOBundle *bundle, aioDou (apply)(aioDou, aioDou));

#endif //AIO_THE_SHORTEST_REPRODUCER_H