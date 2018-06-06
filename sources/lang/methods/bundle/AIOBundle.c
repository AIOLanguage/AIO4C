#include <malloc.h>
#include "../../../../headers/lib/collections/lists/AIOMutableListOfString.h"
#include "../../../../headers/lang/methods/bundle/AIOBundle.h"

void createAIOBundle(AIOBundle **bundle, AIOMutableListOfString *inputValues) {
    //Create the same bundle:
    *bundle = (AIOBundle *) calloc(1, sizeof(AIOBundle));
    //Set input values:
    (*bundle)->inputValues = inputValues;
    //Create output values:
    AIOMutableListOfString *outputValues;
    createMutableListOfString(&outputValues);
    (*bundle)->outputValues = calloc(1, sizeof(AIOMutableListOfString));
    (*bundle)->outputValues = outputValues;
}

/*
 * /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    AIOBundle* bundle;
    AIOMutableListOfString* inputValues;
    createMutableListOfString(&inputValues);
    addInMutableListOfString(inputValues, "1ut");
    addInMutableListOfString(inputValues, "200y");
    addInMutableListOfString(inputValues, "3vc");
    createAIOBundle(&bundle, inputValues);
    printf("%s", *bundle->inputValues->strings);
 */