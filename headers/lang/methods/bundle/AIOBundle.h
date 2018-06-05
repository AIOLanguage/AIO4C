#ifndef AIO_AIO_BUNDLE_H
#define AIO_AIO_BUNDLE_H

#include "../../../lib/lists/AIOMutableListOfString.h"

typedef struct AIOBundle {
    AIOMutableListOfString* inputValues;
    AIOMutableListOfString* outputValues;
} AIOBundle;

#endif //AIO_AIO_BUNDLE_H