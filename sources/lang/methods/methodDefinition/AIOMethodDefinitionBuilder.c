#include "../../../../headers/lang/methods/methodDefinition/AIOMethodDefinition.h"

AIOMethodDefinition *buildAIOMethodDefinition(char *name, AIOMutableListOfString *sourceCode, int startIndex) {
    //Create the same method definition:
    AIOMethodDefinition *methodDefinition = calloc(1, sizeof(AIOMethodDefinition));
    return methodDefinition;
}

AIOMutableListOfString *getSourceCodeOfMethod(char *methodName, AIOMutableListOfString *sourceCode, int startIndex) {
    AIOMutableListOfString* methodCode;
    createMutableListOfString(&methodCode);
    int currentIndex = startIndex;



//    methodCode.add(sourceCode[currentIndex].trimStart().trimEnd().removePrefix(methodName))
//    //Обязательно между методами существуют пустые строки:
//    while (++currentIndex < sourceCode.size && sourceCode[currentIndex].trimStart().trimEnd() != "") {
//        methodCode.add(sourceCode[currentIndex].trimStart().trimEnd())
//    }
//    return methodCode
}

