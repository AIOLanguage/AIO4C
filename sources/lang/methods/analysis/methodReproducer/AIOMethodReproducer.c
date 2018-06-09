#include "../../../../../headers/lang/methods/bundle/AIOBundle.h"
#include "../../../../../headers/lang/methods/analysis/methodReproducer/AIOMethodReproducer.h"
#include "../../../../../headers/lib/utils/stringUtils/StringUtils.h"
#include "../../../../../headers/lib/utils/operationUtils/OperationUtils.h"
#include "../../../../../headers/lang/methods/analysis/methodReproducer/theShortest/plusForEachReproducer/AIOPlusForEachReproducer.h"
#include "../../../../../headers/lang/methods/analysis/methodReproducer/theShortest/multiplyForEachReproducer/AIOMultiplyForEachReproducer.h"
#include "../../../../../headers/lang/methods/analysis/methodReproducer/theShortest/concatForEachReproducer/AIOConcatForEachReproducer.h"
#include "../../../../../headers/lang/methods/methodDefinition/AIOMethodDefinitionBuilder.h"
#include <mem.h>
#include <stdio.h>
#include <process.h>


void createTheShortestMethodReproducer(AIOTheShortestReproducer **theShortestReproducer) {
    *theShortestReproducer = calloc(1, sizeof(AIOTheShortestReproducer));
    if (*theShortestReproducer == NULL) {
        perror("cannot allocate memory for aio the shortest method reproducer");
        exit(1);
    }
}

void createShortMethodReproducer(AIOShortReproducer **shortReproducer) {
    *shortReproducer = calloc(1, sizeof(AIOTheShortestReproducer));
    if (*shortReproducer == NULL) {
        perror("cannot allocate memory for aio short method reproducer");
        exit(1);
    }
}

void createDefaultMethodReproducer(AIODefaultReproducer **defaultReproducer) {
    *defaultReproducer = calloc(1, sizeof(AIOTheShortestReproducer));
    if (*defaultReproducer == NULL) {
        perror("cannot allocate memory for aio the shortest method reproducer");
        exit(1);
    }
}

void createAIOMethodReproducer(AIOMethodReproducer **methodReproducer, AIOMethodDefinition *methodDefinition,
                               AIOMethodContainer *methodContainer, AIOBundle *bundle) {
    *methodReproducer = calloc(1, sizeof(AIOMethodReproducer));
    if (*methodReproducer == NULL) {
        perror("cannot allocate memory for aio method reproducer");
        exit(1);
    }
    //Create inner method reproducers:
    createTheShortestMethodReproducer(&(*methodReproducer)->shortestReproducer);
    createShortMethodReproducer(&(*methodReproducer)->shortReproducer);
    createDefaultMethodReproducer(&(*methodReproducer)->defaultReproducer);
    //Set aio method definition:
    (*methodReproducer)->methodDefinition = methodDefinition;
    //Set aio method method container:
    (*methodReproducer)->methodContainer = methodContainer;
    //Set bundle:
    (*methodReproducer)->bundle = bundle;
}

void theShortestReproduce(AIOTheShortestReproducer *theShortestReproducer, AIOMethodDefinition *methodDefinition
        , AIOVariableMap* variableMap) {
    printf("The shortest reproducing...\n");
    char *word;
    trim(methodDefinition->sourceCode->strings[0], &word);
    if (isPlusOperation(word) == 0) {
        plusForEachReproduce(variableMap);
        return;
    }
    if (isMultiplyOperation(word) == 0) {
        multiplyForEachReproduce(variableMap);
        return;
    }
    if (isConcatOperation(word)) {
        concatForEachReproduce(variableMap);
        return;
    }
    if (isTheShortestInTheSameObject(word)) {
        char* forEachMethod = calloc(strlen(word), sizeof(char));
        if (forEachMethod == NULL){
            perror("cannot allocate memory for forEachMethod! in theShortestReproduce!");
        }
        removeSuffix(word, "~", &forEachMethod);
        for (int i = 0; i < *variableMap->size; ++i) {

        }


        methodContainer.argList.forEach
        {
            val
            lastAIOObject = AIOObjectManager.lastVisitedObject
            !!
                    val
            newBundle = AIOBundle(mutableListOf(it.value))
            lastAIOObject.methodManager.invokeMethod("@$forEachMethod", newBundle)
            bundle.outputValues.addAll(newBundle.outputValues)
        }
    }
    if (AIOMethodDefinitionBuilder.isTheShortestInTheOtherObject(word)) {
        val aioObjectNameVsMethod = word.split(".@")
        val aioObjectName = aioObjectNameVsMethod[0]
        val aioMethodName = aioObjectNameVsMethod[1].removeSuffix("~")
        var aioObject = AIOObjectManager.getAIOObject(aioObjectName)
        if (aioObject == null) {
            val path = "${AIOObjectManager.lastVisitedObject?.folder!!}/$aioObjectName"
            aioObject = AIOObjectManager.addAIOObject("$path.aio")
        }
        methodContainer.argList.forEach
        {
            val inputValue = it.value
            val newBundle = AIOBundle(mutableListOf(inputValue))
            aioObject.methodManager.invokeMethod("@$aioMethodName", newBundle)
            bundle.outputValues.addAll(newBundle.outputValues)
        }
    }
}

void shortReproduce(AIOShortReproducer *shortReproducer) {

}

void defaultReproduce(AIODefaultReproducer *defaultReproducer) {

}

void reproduceMethod(AIOMethodReproducer *methodReproducer) {
    switch (methodReproducer->methodDefinition->methodSizeType) {
        case THE_SHORTEST:
            theShortestReproduce(methodReproducer->shortestReproducer);
            break;
        case SHORT:
            shortReproduce(methodReproducer->shortReproducer);
            break;
        case DEFAULT:
            defaultReproduce(methodReproducer->defaultReproducer);
            break;
    }
}