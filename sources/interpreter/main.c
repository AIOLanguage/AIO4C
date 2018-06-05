#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../headers/lang/methods/methodDefinition/AIOMethodDefinition.h"
#include "../../headers/lib/maps/AIOMutableMethodDefinitionMap.h"
#include "../../headers/lang/object/AIOObject.h"

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
    printf("%s\n", definition->name);

    //Create method definition map:
    AIOMutableMethodDefinitionMap* methodDefinitionMap;
    createMutableMapOfDefinitions(&methodDefinitionMap);

    putInMutableMapOfDefinitions(methodDefinitionMap, definition);

    //Create method manager:
    AIOMethodManager* methodManager;
    createAIOMethodManager(&methodManager, methodDefinitionMap);

    //Create AIO object:
    AIOObject* aioObject;
    createAIOObject(&aioObject, methodManager, "starter");
    printf("%s", aioObject->name);
    return 0;
}