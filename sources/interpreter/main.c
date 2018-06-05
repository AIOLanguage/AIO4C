#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../headers/lang/methods/methodDefinition/AIOMethodDefinition.h"

//AIOObjectManager aioObjectManager;

int main() {
    //Create methodName:
    char* methodName = "@main";
    //Create declaration:
    AIOMutableListOfString* args;
    createMutableListOfString(&args);
    printf("%d\n", *args->size);
    AIODeclaration* declaration;
    createAIODeclaration(&declaration, methodName, args);
    printf("%s\n", declaration->methodName);
    //Create annotation list:
    AIOMutableListOfAnnotations* annotations;
    createMutableListOfAnnotations(&annotations);
    printf("%d\n", *annotations->size);
    //Create source code:
    AIOMutableListOfString* sourceCode;
    createMutableListOfString(&sourceCode);
    //Create method size type:
    enum AIOMethodSizeType methodSizeType = DEFAULT;
    AIOMethodDefinition *definition;
    createAIOMethodDefinition(&definition, methodName, declaration, annotations, sourceCode, &methodSizeType);
    printf("%s", definition->name);
    return 0;
}