#include <malloc.h>
#include "../../../headers/lang/annotations/AIOAnnotation.h"

void createAIOAnnotation(AIOAnnotation **annotation) {
    *annotation = (AIOAnnotation *) calloc(1, sizeof(AIOAnnotation));
}