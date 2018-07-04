#ifndef AIO_METHOD_REPRODUCER_H
#define AIO_METHOD_REPRODUCER_H

#include "../../../lang/methods/bundle/aio_bundle.h"
#include "../../../lang/methods/aio_method_container.h"
#include "default/aio_default_reproducer.h"
#include "short/aio_short_reproducer.h"
#include "../../../lang/object/aio_file.h"

void reproduce_method(aio_file *object, aio_method_definition *method_definition,
                      aio_method_container *method_container, aio_bundle *bundle);

#endif //AIO_METHOD_REPRODUCER_H