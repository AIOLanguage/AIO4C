#ifndef AIO_METHOD_REPRODUCER_H
#define AIO_METHOD_REPRODUCER_H

#include "../../methodDefinition/aio_method_definition.h"
#include "../../bundle/aio_bundle.h"
#include "../../AIOMethodContainer.h"
#include "theShortest/aio_the_shortest_reproducer.h"
#include "default/aio_default_reproducer.h"
#include "short/aio_short_reproducer.h"
#include "../../../object/AIOObject.h"

void reproduceMethod(aio_object *object, aio_method_definition *method_definition,
                     aio_method_container *method_container, aio_bundle *bundle);

#endif //AIO_METHOD_REPRODUCER_H