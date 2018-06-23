#include <stdio.h>
#include "../../../../../../headers/lang/object/AIOObject.h"
#include "../../../../../../headers/lib/collections/maps/AIOVariableMap.h"
#include "../../../../../../headers/lang/methods/AIOMethodContainer.h"
#include "../../../../../../headers/lang/methods/analysis/methodReproducer/theShortest/concatForEachReproducer/AIOConcatForEachReproducer.h"
#include "../../../../../../headers/lib/utils/operationUtils/OperationUtils.h"
#include "../../../../../../headers/lang/methods/analysis/methodReproducer/theShortest/multiplyForEachReproducer/AIOMultiplyForEachReproducer.h"
#include "../../../../../../headers/lang/methods/analysis/methodReproducer/theShortest/plusForEachReproducer/AIOPlusForEachReproducer.h"
#include "../../../../../../headers/lang/object/objectManager/AIOObjectManager.h"
#include "../../../../../../headers/lib/utils/fileUtils/FileUtils.h"
#include "../../../../../../headers/lang/methods/methodDefinition/AIOMethodDefinitionBuilder.h"

void makeForEachCustomMethodInvocation(AIOObject *nextObject, AIOVariableMap *variableMap, char *nextMethodName,
                                       AIOBundle *bundle) {
    for (int i = 0; i < *variableMap->size; ++i) {
        AIOBundle *newBundle;
        StringList *valueList;
        createListOfString(&valueList);
        addInListOfString(valueList, variableMap->variables[i]->value);
        createAIOBundle(&newBundle, valueList);
        invokeMethodInManager(nextObject, nextMethodName, newBundle);
        for (int j = 0; j < *newBundle->outputValues->size; ++j) {
            addInListOfString(bundle->outputValues, newBundle->outputValues->strings[j]);
        }
    }
}

void reproduceTheShortestMethod(AIOObject *object, AIOMethodDefinition *methodDefinition,
                                AIOMethodContainer *methodContainer, AIOBundle *bundle) {
    printf("The shortest reproducing...\n");
    char *word;
    trim(methodDefinition->sourceCode->strings[0], &word);
    AIOVariableMap *argMap = methodContainer->variableMap;
    if (isPlusOperation(word) == 0) {
        plusForEachReproduce(argMap, bundle);
        return;
    }
    if (isMultiplyOperation(word) == 0) {
        multiplyForEachReproduce(argMap, bundle);
        return;
    }
    if (isConcatOperation(word) == 0) {
        concatForEachReproduce(argMap, bundle);
        return;
    }
    //뭔가 있을지도 모른다.
    if (isTheShortestInTheSameObject(word)) {
        char *nextMethodName = calloc(strlen(word), sizeof(char));
        if (nextMethodName == NULL) {
            perror("cannot allocate memory for nextMethodName! in reproduceTheShortestMethod!");
        }
        removeSuffix(word, "~", &nextMethodName);
        makeForEachCustomMethodInvocation(object, methodContainer->variableMap, nextMethodName, bundle);
    }
    if (isTheShortestInTheOtherObject(word)) {
        char **nextObjectNameVsMethod;
        splitByChar(word, '.', &nextObjectNameVsMethod);
        char *nextObjectPathPlusName = nextObjectNameVsMethod[0];
        char *nextMethodName;
        removeSuffix(nextObjectNameVsMethod[1], "~", &nextMethodName);
        AIOObject *nextObject = getAIOObjectInMapByName(aioObjectManager->objectMap, nextObjectPathPlusName);
        char *nextObjectName;
        if (nextObject == NULL) {
            StringPair *relativePathVsObjectName = extractNameAndFolderPathFromPath(nextObjectPathPlusName);
            char *relativeNextObjectPath = relativePathVsObjectName->first;
            char *absoluteNextObjectPath;
            mergeNewFolderPath(object->folderPath, relativeNextObjectPath, &absoluteNextObjectPath);
            buildAIOObjectAndPutInAIOObjectManager(aioObjectManager, absoluteNextObjectPath);
            nextObjectName = relativePathVsObjectName->second;
        } else {
            nextObjectName = nextObjectPathPlusName;
        }
        nextObject = getAIOObjectInMapByName(aioObjectManager->objectMap, nextObjectName);
        makeForEachCustomMethodInvocation(nextObject, methodContainer->variableMap, nextMethodName, bundle);
    }
}

//Abstract operations for int and dou:
int
intOperationForEachTypeOperationReproduce(AIOVariableMap *argMap, AIOBundle *bundle, aioInt (apply)(aioInt, aioInt)) {
    if (*(argMap->variables[0]->type) == AIO_INT) {
        aioInt *result;
        strToInt(argMap->variables[0]->value, &result);
        for (int i = 1; i < *argMap->size; ++i) {
            aioInt *argValue;
            strToInt(argMap->variables[i]->value, &argValue);
            *result = apply(*result, *argValue);
        }
        aioStr outputResult;
        intToStr(*result, &outputResult);
        addInListOfString(bundle->outputValues, outputResult);
        return 0;
    }
    return 1;
}

int
douOperationForEachTypeOperationReproduce(AIOVariableMap *argMap, AIOBundle *bundle, aioDou (apply)(aioDou, aioDou)) {
    if (*(argMap->variables[0]->type) == AIO_DOU) {
        aioDou *result;
        strToDou(argMap->variables[0]->value, &result);
        for (int i = 1; i < *argMap->size; ++i) {
            aioDou *argValue;
            strToDou(argMap->variables[i]->value, &argValue);
            *result = apply(*result, *argValue);
        }
        aioStr outputResult;
        douToStr(*result, &outputResult);
        addInListOfString(bundle->outputValues, outputResult);
        return 0;
    }
    return 1;
}