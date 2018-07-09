#include "../../../../../../headers/lib/collections/maps/aio_variable_map.h"
#include "../../../../../../../headers/lang/methods/bundle/aio_bundle.h"
#include "../../../../../../../headers/lang/methods/aio_method_container.h"
#include "../../../../../../../headers/lang/methods/analysis/method_reproducer/the_shortest/aio_the_shortest_reproducer.h"

aio_int multiply_int(aio_int first, aio_int second) {
    return first * second;
}

aio_dou multiply_dou(aio_dou first, aio_dou second) {
    return first * second;
}

int int_multiply_for_each_type_operation_reproduce(aio_variable_map *arg_map, aio_bundle *bundle) {
    int_operation_for_each_type_operation_reproduce(arg_map, bundle, multiply_int);
}

int dou_multiply_for_each_type_operation_reproduce(aio_variable_map *arg_map, aio_bundle *bundle) {
    return dou_operation_for_each_type_operation_reproduce(arg_map, bundle, multiply_dou);
}

void multiply_for_each_reproduce(aio_variable_map *arg_map, aio_bundle *bundle) {
    if (arg_map->size != 0) {
        if (int_multiply_for_each_type_operation_reproduce(arg_map, bundle) == 1) {
            return;
        }
        if (dou_multiply_for_each_type_operation_reproduce(arg_map, bundle) == 1) {
            return;
        }
        // 아마있을거야 long 또는 float =)
    }
}