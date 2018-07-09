#include <stddef.h>
#include <stdio.h>
#include <process.h>
#include "../../../../headers/lang/methods/method_definition/aio_method_definition.h"

//Passed JUnitTest!
aio_method_definition *new_aio_method_definition(char *name, aio_declaration *declaration,
                                                 aio_annotation_list *annotations, string_list *source_code,
                                                 enum aio_method_size_type method_size_type) {
    //Create the same definition:
    aio_method_definition *method_definition = calloc(1, sizeof(aio_method_definition));
    if (method_definition == NULL) {
        perror("cannot allocate memory for aio method definition");
        exit(1);
    }
    //Set definition name:
    method_definition->name = name;
    //Set declaration:
    method_definition->declaration = declaration;
    //Set annotation list:
    method_definition->annotations = annotations;
    //Set source code:
    method_definition->source_code = source_code;
    //Set method size type:
    method_definition->method_size_type = method_size_type;
    return method_definition;
}