#include "../../../../../../../headers/lib/collections/maps/AIOVariableMap.h"
#include "../../../../../../../headers/lang/methods/bundle/aio_bundle.h"
#include "../../../../../../../headers/lang/methods/AIOMethodContainer.h"
#include "../../../../../../../headers/lang/methods/analysis/methodReproducer/theShortest/aio_the_shortest_reproducer.h"

aio_int plus_int(aio_int first, aio_int second) {
    return first + second;
}

aio_dou plus_dou(aio_dou first, aio_dou second) {
    return first + second;
}

int int_plus_for_each_type_operation_reproduce(aio_variable_map *arg_map, aio_bundle *bundle) {
    int_operation_for_each_type_operation_reproduce(arg_map, bundle, plus_int);
}

int dou_plus_for_each_type_operation_reproduce(aio_variable_map *arg_map, aio_bundle *bundle) {
    return dou_operation_for_each_type_operation_reproduce(arg_map, bundle, plus_dou);
}

void plus_for_each_reproduce(aio_variable_map *arg_map, aio_bundle *bundle) {
    if (arg_map->size != 0) {
        if (int_plus_for_each_type_operation_reproduce(arg_map, bundle) == 0) {
            return;
        }
        if (dou_plus_for_each_type_operation_reproduce(arg_map, bundle) == 0) {
            return;
        }
        // 아마있을거야 long 또는 float =)
    }
}