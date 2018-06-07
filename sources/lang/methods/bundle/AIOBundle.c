#include <malloc.h>
#include "../../../../headers/lib/collections/lists/StringList.h"
#include "../../../../headers/lang/methods/bundle/AIOBundle.h"

//Passed JUnitTest!
void createAIOBundle(AIOBundle **bundle, StringList *inputValues) {
    //Create the same bundle:
    *bundle = (AIOBundle *) calloc(1, sizeof(AIOBundle));
    //Set input values:
    (*bundle)->inputValues = inputValues;
    //Create output values:
    StringList *outputValues;
    createListOfString(&outputValues);
    (*bundle)->outputValues = calloc(1, sizeof(StringList));
    (*bundle)->outputValues = outputValues;
}

/*
 * /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    AIOBundle* bundle;
    StringList* inputValues;
    createListOfString(&inputValues);
    addInMutableListOfString(inputValues, "1ut");
    addInMutableListOfString(inputValues, "200y");
    addInListOfString(inputValues, "3vc");
    createAIOBundle(&bundle, inputValues);
    printf("%s", *bundle->inputValues->strings);
 */