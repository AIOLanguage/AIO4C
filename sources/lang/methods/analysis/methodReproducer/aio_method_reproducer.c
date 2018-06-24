#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../../headers/lang/object/aio_object.h"
#include "../../../../../headers/lang/methods/aio_method_container.h"
#include "../../../../../headers/lang/methods/analysis/methodReproducer/theShortest/aio_the_shortest_reproducer.h"
#include "../../../../../headers/lang/methods/analysis/methodReproducer/short/aio_short_reproducer.h"
#include "../../../../../headers/lang/methods/analysis/methodReproducer/default/aio_default_reproducer.h"
#include "../../../../../headers/lang/methods/analysis/methodReproducer/aio_method_reproducer.h"

void reproduceMethod(aio_object *object, aio_method_definition *method_definition, aio_method_container *method_container,
                     aio_bundle *bundle) {
    switch (method_definition->method_size_type) {
        case THE_SHORTEST:
            reproduceTheShortestMethod(object, method_definition, method_container, bundle);
            break;
        case SHORT:
            reproduce_short_method(object, method_definition, method_container, bundle,
                                   method_definition->source_code->strings[0]);
            break;
        case DEFAULT:
            reproduce_default_method(object, method_definition, method_container, bundle);
            break;
    }
}