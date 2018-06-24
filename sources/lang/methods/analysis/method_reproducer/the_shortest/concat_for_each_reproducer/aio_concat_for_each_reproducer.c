#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../../../../../headers/lib/collections/maps/aio_variable_map.h"
#include "../../../../../../../headers/lang/methods/bundle/aio_bundle.h"
#include "../../../../../../../headers/lib/utils/string_utils/string_utils.h"

void concat_for_each_reproduce(aio_variable_map *arg_map, aio_bundle *bundle) {
    if (*(arg_map->variables[0]->type) == AIO_STR) {
        size_t length = 0;
        //카운트 길이:
        for (int i = 0; i < arg_map->size; ++i) {
            length += strlen(arg_map->variables[i]->value);
        }
        aio_str result = calloc(length + 1, sizeof(char));
        if (result == NULL) {
            perror("cannot allocate memory for result in concat_for_each_reproduce!");
            exit(1);
        }
        strcpy(result, arg_map->variables[0]->value);
        for (int i = 1; i < arg_map->size; ++i) {
            concat_string_to_string(result, arg_map->variables[i]->value);
        }
        add_in_string_list(bundle->output_values, result);
    }
}