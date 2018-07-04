#include <mem.h>
#include <malloc.h>
#include <stdio.h>
#include <process.h>
#include "../../../headers/lang/object/object_manager/aio_nexus.h"
#include "../../../headers/lang/methods/method_definition/aio_method_definition_builder.h"
#include "../../../headers/lib/pair/string_pair.h"
#include "../../../headers/lib/utils/file_utils/file_utils.h"
#include "../../../headers/lang/methods/aio_method.h"

aio_nexus *core;

//Passed JUnitTest!
aio_method_manager *new_aio_method_manager(aio_method_definition_map *method_definition_map) {
    //Create method manager:
    aio_method_manager *method_manager = calloc(1, sizeof(aio_method_manager));
    if (method_manager == NULL) {
        perror("cannot allocate memory for aio method manager!");
        exit(1);
    }
    //Set method definition map:
    method_manager->method_definition_map = method_definition_map;
    //Set boolean "has main": (default false)
    method_manager->has_main = -1;
    return method_manager;
}

//Passed JUnitTest!
void find_methods_in_manager(aio_file *aio_object) {
    for (int i = 0; i < aio_object->source_code->size; ++i) {
        char *line = aio_object->source_code->strings[i];
        int length = strlen(line);
        if (length > 1) {
            //starts with @
            if (line[0] == '@') {
                unsigned name_size = 1;
                char pointer;
                for (int j = 1; j < length; ++j) {
                    if (line[j] == ' ') {
                        if (j == 1) {
                            perror("incorrect method name @");
                        }
                        break;
                    }
                    name_size = name_size + 1;
                }
                char *method_name = calloc(name_size + 1, sizeof(char));
                for (int k = 0; k < name_size; ++k) {
                    method_name[k] = line[k];
                }
                if (strcmp(method_name, "@main") == 0) {
                    aio_object->method_manager->has_main = 0;
                }
                aio_method_definition *method_definition = build_aio_method_definition(method_name,
                                                                                       aio_object->source_code, i);
                put_aio_method_definition_in_map(aio_object->method_manager->method_definition_map, method_definition);
            }
        }
    }
}

#define CHUNK 1024

//Path example:
//"../aioPrograms/test.txt", "r"
//Passed JUnitTest!
void load_source_code_in_aio_object(aio_file *object, char *path) {
    printf("Loading source code...\n");
    //Create source code mutable_by_type list:
    string_list *source_code = new_string_list();
    //Create file:
    FILE *file;
    //Create line buffer:
    char buffer[CHUNK];
    if ((file = fopen(path, "r")) == NULL) {
        perror("cannot open source-file");
        exit(1);
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strlen(buffer) - 1] = '\0';
        //Create string:
        char *line = calloc(1, CHUNK);
        strcpy(line, buffer);
        //put string in list:
        add_in_string_list(source_code, line);
    }
    fclose(file);
    //Set source code:
    object->source_code = source_code;
}

//Passed JUnitTest!
aio_file *new_aio_file(aio_method_manager *method_manager, char *path) {
    //Create the same aio_file:
    aio_file *object = calloc(1, sizeof(aio_file));
    if (object == NULL) {
        perror("cannot allocate memory for aio aio_file!");
        exit(1);
    }
    //Set method manager:
    object->method_manager = method_manager;
    //Set name from path:
    string_pair *nameVsFolder = extract_name_and_folder_path_from_path(path);
    object->name = nameVsFolder->first;
    //Set folder path from path:
    object->folder_path = nameVsFolder->second;
    //Loading code:
    load_source_code_in_aio_object(object, path);
    find_methods_in_manager(object);
    return object;
}

void invoke_method_in_manager(aio_file *object, char *method_name, aio_bundle *bundle) {
    aio_method_definition *method_definition = get_aio_method_definition_in_map_by_name(
            object->method_manager->method_definition_map, method_name);
    if (method_definition->declaration != NULL) {
        if (method_definition->declaration->argList->size != bundle->input_values->size) {
            perror("number of args not matches with arg size of declaration!");
            exit(1);
        }
    }
    invoke_new_aio_method(object, method_definition, bundle);
}