#ifndef AIO_ABSTRACT_FOR_EACH_OPERATION_REPRODUCER_H
#define AIO_ABSTRACT_FOR_EACH_OPERATION_REPRODUCER_H


#include "../../../AIOMethodContainer.h"
#include "../../../bundle/AIOBundle.h"

abstract fun createAIOType(): AIOType

    abstract fun apply(result: T, value: T): T

    //List is not empty:
    void reproduceForEachIntOperationReproducer(AIOVariableMap* argMap, AIOMethodContainer* methodContainer, AIOBundle* bundle) {
        val firstAIOVariable = argList[0]
        val firstValue = firstAIOVariable.value
        val aioType = this.createAIOType()


        if(argMap[0])




        if (aioType.matches(firstValue)) {
            firstAIOVariable.type = aioType
            var result = aioType.toType(firstValue) as T
            for (i in 1 until argList.size) {
                val aioVariable = argList[i]
                val value = aioVariable.value
                if (firstAIOVariable.type.matches(value)) {
                    val intValue = aioType.toType(value) as T
                    result = this.apply(result, intValue)
                } else {
                    throw AIOIncomparableTypesException()
                }
            }
            this.bundle.outputValues.add(result.toString())
        }
    }
}




#endif //AIO_ABSTRACT_FOR_EACH_OPERATION_REPRODUCER_H