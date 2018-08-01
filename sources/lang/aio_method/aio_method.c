#include <mem.h>
#include <stdio.h>
#include <process.h>
#include "../../../headers/lang/methods/aio_method.h"
#include "../../../headers/lang/object/aio_file.h"
#include "../../../headers/lib/utils/string_utils/string_utils.h"
#include "../../../headers/reserved_names/aio_reserved_names_container.h"
#include "../../../headers/lang/methods/analysis/method_reproducer/aio_method_reproducer.h"

aio_method_container *new_aio_method_container() {
    //Create the same aio method container:
    aio_method_container *container = calloc(1, sizeof(aio_method_container));
    if (container == NULL) {
        perror("can not allocate memory for aio method container!");
        exit(1);
    }
    //Create arg map:
    container->arg_map = new_aio_variable_map();
    //Create variable map:
    container->variable_map = new_aio_variable_map();
    return container;
}

void set_args_in_method_container(aio_method_container *method_container, aio_declaration *declaration,
                                  string_list *input_args) {
    //I checked args size with declaration before creating of method!
    if (declaration != NULL) {
        for (int i = 0; i < declaration->argList->size; ++i) {
            //Input args is immutable:
            //Compare input value type:
            enum aio_type type;
            set_type(input_args->strings[i], &type);
            aio_variable *arg = new_aio_variable(declaration->argList->strings[i], input_args->strings[i], -1, &type);
            put_in_aio_variable_in_map(method_container->arg_map, arg);
        }
    } else {
        for (int i = 0; i < input_args->size; i++) {
            //Input args is immutable:
            //Compare input value type:
            enum aio_type type;
            set_type(input_args->strings[i], &type);
            char *implicit_argument_name = "<<";
            char *index = int_to_str(i);
            concat_string_to_string(implicit_argument_name, index);
            aio_variable *arg = new_aio_variable(implicit_argument_name, input_args->strings[i], -1, &type);
            put_in_aio_variable_in_map(method_container->arg_map, arg);
        }
    }
}

int contains_variable_in_map(const char *variable_name, const aio_variable_map *variable_map) {
    for (int i = 0; i < variable_map->size; ++i) {
        if (strcmp(variable_name, variable_map->names[i]) == 0) {
            return 0;
        }
    }
    return 1;
}


int contains_variable(char *variable_name, aio_method_container *method_container) {
    const aio_variable_map *argMap = method_container->arg_map;
    const aio_variable_map *variabl_map = method_container->variable_map;
    if (contains_variable_in_map(variable_name, argMap) == 0) {
        return 0;
    }
    if (contains_variable_in_map(variable_name, variabl_map)) {
        return 0;
    }
    return 1;
}

void set_variable(aio_variable *variable, aio_method_container *method_container) {
    if (can_use_name(variable->name) == 0 && contains_variable(variable->name, method_container) == 0) {
        put_in_aio_variable_in_map(method_container->variable_map, variable);
    } else {
        perror("there is variable already exists!");
        exit(1);
    }
}

void invoke_new_aio_method(aio_file *aio_context, aio_method_definition *method_definition, aio_bundle *bundle) {
    //Create the same aio method:
    aio_method *method = calloc(1, sizeof(aio_method));
    if (method == NULL) {
        perror("cannot allocate memory for aio method");
        exit(1);
    }
    //Create method container:
    method->method_container = new_aio_method_container();
    //Set args:
    set_args_in_method_container(method->method_container, method_definition->declaration, bundle->input_values);
    //Reproduce method:
    reproduce_method(aio_context, method_definition, method->method_container, bundle);
}