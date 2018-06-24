#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../headers/lang/methods/aio_method.h"
#include "../../../headers/lang/object/aio_object.h"
#include "../../../headers/lib/utils/stringUtils/string_utils.h"

void createAIOMethodContainer(aio_method_container **container) {
    //Create the same aio method container:
    *container = calloc(1, sizeof(aio_method_container));
    if (*container == NULL) {
        perror("can not allocate memory for aio method container!");
    }
    //Create arg map:
    new_aio_variable_map(&(*container)->argMap);
    //Create variable map:
    new_aio_variable_map(&(*container)->variable_map);
}

void setArgs(aio_method_container *methodContainer, aio_declaration *declaration, string_list *inputArgs) {
    //I checked args size with declaration before creating of method!
    if (declaration != NULL) {
        for (int i = 0; i < *declaration->argList->size; ++i) {
            //Input args is immutable:
            //Compare input value type:
            aio_variable *argument;
            enum aio_type type;
            set_type(inputArgs->strings[i], &type);
            new_aio_variable(&argument, declaration->argList->strings[i], inputArgs->strings[i], -1, &type);
            put_in_aio_variable_in_map(methodContainer->argMap, argument);
        }
    } else {
        for (int i = 0; i < *inputArgs->size; i++) {
            //Input args is immutable:
            //Compare input value type:
            aio_variable *argument;
            enum aio_type type;
            set_type(inputArgs->strings[i], &type);
            char *implicitArgumentName = "<<";
            char *index;
            int_to_str(i, &index);
            strcat(implicitArgumentName, index);
            new_aio_variable(&argument, implicitArgumentName, inputArgs->strings[i], -1, &type);
            put_in_aio_variable_in_map(methodContainer->argMap, argument);
        }
    }
}

int contains_variable_in_map(const char *variable_name, const aio_variable_map *variable_map) {
    for (int i = 0; i < *variable_map->size; ++i) {
        if (strcmp(variable_name, variable_map->names[i]) == 0) {
            return 0;
        }
    }
    return 1;
}


int contains_variable(char *variable_name, aio_method_container *method_container) {
    const aio_variable_map *argMap = method_container->argMap;
    const aio_variable_map *variableMap = method_container->variable_map;
    if (contains_variable_in_map(variable_name, argMap) == 0) {
        return 0;
    }
    if (contains_variable_in_map(variable_name, variableMap)) {
        return 0;
    }
    return 1;
}

void set_variable(aio_variable *variable, aio_method_container *method_container) {
    if (canUseName(variable->name) == 0 && contains_variable(variable->name, method_container) == 0) {
        put_in_aio_variable_in_map(method_container->variable_map, variable);
    } else {
        perror("there is variable already exists!");
        exit(1);
    }
}

void new_aio_method_and_invoke(aio_object *object, aio_method **method, aio_method_definition *methodDefinition,
                               aio_bundle *bundle) {
    //Create the same aio method:
    *method = calloc(1, sizeof(aio_method));
    if (*method == NULL) {
        perror("cannot allocate memory for aio method");
        exit(1);
    }
    //Create method container:
    createAIOMethodContainer(&(*method)->methodContainer);
    //Set args:
    setArgs((*method)->methodContainer, methodDefinition->declaration, bundle->input_values);
    //Reproduce method:
    reproduceMethod(object, methodDefinition, (*method)->methodContainer, bundle);
}