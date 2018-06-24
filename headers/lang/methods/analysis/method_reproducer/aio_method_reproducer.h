#ifndef AIO_METHOD_REPRODUCER_H
#define AIO_METHOD_REPRODUCER_H

#include "../../bundle/aio_bundle.h"
#include "../../aio_method_container.h"
#include "default/aio_default_reproducer.h"
#include "short/aio_short_reproducer.h"
#include "../../../object/aio_object.h"

void reproduce_method(aio_object *object, aio_method_definition *method_definition,
                      aio_method_container *method_container, aio_bundle *bundle);

#endif //AIO_METHOD_REPRODUCER_H