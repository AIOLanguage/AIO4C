#ifndef AIO_AIO_BUNDLE_H
#define AIO_AIO_BUNDLE_H

#include "../../../lib/collections/lists/AIOMutableListOfString.h"

typedef struct AIOBundle {
    AIOMutableListOfString* inputValues;
    AIOMutableListOfString* outputValues;
} AIOBundle;

void createAIOBundle(AIOBundle** bundle, AIOMutableListOfString* inputValues);

#endif //AIO_AIO_BUNDLE_H