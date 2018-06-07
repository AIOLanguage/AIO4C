#ifndef AIO_AIO_BUNDLE_H
#define AIO_AIO_BUNDLE_H

#include "../../../lib/collections/lists/StringList.h"

typedef struct AIOBundle {
    StringList* inputValues;
    StringList* outputValues;
} AIOBundle;

void createAIOBundle(AIOBundle** bundle, StringList* inputValues);

#endif //AIO_AIO_BUNDLE_H