#include <stdio.h>
#include <process.h>
#include "../../../../../../headers/lang/object/aio_object.h"
#include "../../../../../../headers/lib/collections/maps/aio_variable_map.h"
#include "../../../../../../headers/lang/methods/aio_method_container.h"
#include "../../../../../../headers/lang/methods/analysis/methodReproducer/theShortest/concatForEachReproducer/aio_concat_for_each_reproducer.h"
#include "../../../../../../headers/lib/utils/operationUtils/operation_utils.h"
#include "../../../../../../headers/lang/methods/analysis/methodReproducer/theShortest/multiplyForEachReproducer/aio_multiply_for_each_reproducer.h"
#include "../../../../../../headers/lang/methods/analysis/methodReproducer/theShortest/plusForEachReproducer/aio_plus_for_each_reproducer.h"
#include "../../../../../../headers/lang/object/objectManager/AIOObjectManager.h"
#include "../../../../../../headers/lib/utils/fileUtils/file_utils.h"
#include "../../../../../../headers/lang/methods/methodDefinition/aio_method_definition_builder.h"
#include "../../../../../../headers/lib/pair/string_pair.h"

void make_for_each_custom_method_invocation(aio_object *next_object, aio_variable_map *variable_map,
                                            char *next_method_name, aio_bundle *bundle) {
    for (int i = 0; i < *variable_map->size; ++i) {
        string_list *value_list = new_string_list();
        add_in_string_list(value_list, variable_map->variables[i]->value);
        aio_bundle *new_bundle = new_aio_bundle(value_list);
        invoke_method_in_manager(next_object, next_method_name, new_bundle);
        for (int j = 0; j < new_bundle->output_values->size; ++j) {
            add_in_string_list(bundle->output_values, new_bundle->output_values->strings[j]);
        }
    }
}

void reproduceTheShortestMethod(aio_object *object, aio_method_definition *method_definition,
                                aio_method_container *method_container, aio_bundle *bundle) {
    printf("the shortest reproducing...\n");
    char *word = trim(method_definition->source_code->strings[0]);
    aio_variable_map *arg_map = method_container->variable_map;
    if (is_plus_operation(word) == 0) {
        plus_for_each_reproduce(arg_map, bundle);
        return;
    }
    if (is_multiply_operation(word) == 0) {
        multiply_for_each_reproduce(arg_map, bundle);
        return;
    }
    if (is_concat_operation(word) == 0) {
        concat_for_each_reproduce(arg_map, bundle);
        return;
    }
    //뭔가 있을지도 모른다.
    if (is_the_shortest_in_the_same_object(word)) {
        char *next_method_name = remove_suffix(word, "~");
        make_for_each_custom_method_invocation(object, method_container->variable_map, next_method_name, bundle);
    }
    if (is_the_shortest_in_the_other_object(word)) {
        char **next_object_name_vs_method = split_by_string(word, ".");
        char *next_object_path_plus_name = next_object_name_vs_method[0];
        char *next_method_name = remove_suffix(next_object_name_vs_method[1], "~");
        aio_object *next_object = get_aio_object_in_map_by_name(aio_object_manager->objectMap,
                                                                next_object_path_plus_name);
        char *next_object_name;
        if (next_object == NULL) {
            string_pair *relative_path_vs_object_name = extract_name_and_folder_path_from_path(
                    next_object_path_plus_name);
            char *relative_next_object_path = relative_path_vs_object_name->first;
            char *absolute_next_object_path;
            merge_new_folder_path(object->folder_path, relative_next_object_path, &absolute_next_object_path);
            build_aio_object_and_put_in_object_manager(aio_object_manager, absolute_next_object_path);
            next_object_name = relative_path_vs_object_name->second;
        } else {
            next_object_name = next_object_path_plus_name;
        }
        next_object = get_aio_object_in_map_by_name(aio_object_manager->objectMap, next_object_name);
        make_for_each_custom_method_invocation(next_object, method_container->variable_map, next_method_name, bundle);
    }
}

//Abstract operations for int and dou:
int int_operation_for_each_type_operation_reproduce(aio_variable_map *arg_map, aio_bundle *bundle,
                                                    aio_int (apply)(aio_int, aio_int)) {
    if (*(arg_map->variables[0]->type) == AIO_INT) {
        aio_int *result;
        str_to_int(arg_map->variables[0]->value, &result);
        for (int i = 1; i < *arg_map->size; ++i) {
            aio_int *argValue;
            str_to_int(arg_map->variables[i]->value, &argValue);
            *result = apply(*result, *argValue);
        }
        aio_str output_result;
        int_to_str(*result, &output_result);
        add_in_string_list(bundle->output_values, output_result);
        return 0;
    }
    return 1;
}

int dou_operation_for_each_type_operation_reproduce(aio_variable_map *arg_map, aio_bundle *bundle,
                                                    aio_dou (apply)(aio_dou, aio_dou)) {
    if (*(arg_map->variables[0]->type) == AIO_DOU) {
        aio_dou *result;
        str_to_dou(arg_map->variables[0]->value, &result);
        for (int i = 1; i < *arg_map->size; ++i) {
            aio_dou *arg_value;
            str_to_dou(arg_map->variables[i]->value, &arg_value);
            *result = apply(*result, *arg_value);
        }
        aio_str output_result;
        dou_to_str(*result, &output_result);
        add_in_string_list(bundle->output_values, output_result);
        return 0;
    }
    return 1;
}