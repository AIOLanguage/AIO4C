#include <malloc.h>
#include "../../../headers/lang/annotations/AIOAnnotation.h"

//Passed JUnitTest!
void createAIOAnnotation(AIOAnnotation **annotation, char *methodName, char *annotationType) {
    //Create the same annotation:
    *annotation = (AIOAnnotation *) calloc(1, sizeof(AIOAnnotation));
    //Set annotation name:
    (*annotation)->methodName = methodName;
    //Set annotation type:
    (*annotation)->annotationType = annotationType;
}