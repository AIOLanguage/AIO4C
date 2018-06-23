#ifndef AIO_THE_SHORTEST_REPRODUCER_H
#define AIO_THE_SHORTEST_REPRODUCER_H

#include "../../../../object/AIOObject.h"

void reproduceTheShortestMethod(AIOObject *object, AIOMethodDefinition *methodDefinition,
                                AIOMethodContainer *methodContainer, AIOBundle *bundle);

int
intOperationForEachTypeOperationReproduce(AIOVariableMap *argMap, AIOBundle *bundle, AIOInt (apply)(AIOInt, AIOInt));

int
douOperationForEachTypeOperationReproduce(AIOVariableMap *argMap, AIOBundle *bundle, AIODou (apply)(AIODou, AIODou));

#endif //AIO_THE_SHORTEST_REPRODUCER_H