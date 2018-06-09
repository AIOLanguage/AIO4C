#ifndef AIO_PLUS_FOR_EACH_REPRODUCER_H
#define AIO_PLUS_FOR_EACH_REPRODUCER_H

#include "../../../../../../../headers/lang/object/AIOObject.h"
#include "../../../../../../../headers/lib/utils/stringUtils/StringUtils.h"
#include "../../../../../../../headers/lang/methods/AIOMethodContainer.h"
#include "../../../../../../../headers/lang/methods/analysis/methodReproducer/theShortest/AIOAbstractForEachOperationReproducer.h"

void plusForEachReproduce(AIOObject *object, AIOMethodDefinition *methodDefinition,
                          AIOMethodContainer *methodContainer, AIOBundle *bundle);

#endif //AIO_PLUS_FOR_EACH_REPRODUCER_H