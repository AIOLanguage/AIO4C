#include "../../../../headers/lang/object/aio_file.h"
#include "../../../../headers/lib/pair/string_pair.h"
#include "../../../../headers/lib/utils/string_utils/string_utils.h"
#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include <process.h>

char *merge_new_folder_path(char *folder_path, char *next_object_name) {
    //Not supported:
    //While easy make concat_string_to_string =)
    char **paths = calloc(2, sizeof(char *));
    paths[0] = folder_path;
    paths[1] = next_object_name;
    return join_to_string(paths, "", 2);
}


//Passed JUnitTest!
string_pair *extract_name_and_folder_path_from_path(char *path) {
    //*.aio:
    int path_length = strlen(path);
    if (path_length > 4) {
        //without last .aio:
        int start_of_object_name = 0;
        char pointer;
        int end_of_object_name = path_length - 5;
        for (int i = end_of_object_name; i >= 0; --i) {
            pointer = path[i];
            if (pointer == '/') {
                break;
            }
            start_of_object_name = i;
        }
        unsigned size = (unsigned int) (end_of_object_name - start_of_object_name + 1);
        char *object_name = calloc(size + 1, sizeof(char));
        if (object_name == NULL) {
            perror("can not allocate memory for aio_context name!");
            exit(1);
        }
        for (int j = 0; j < size; ++j) {
            object_name[j] = path[j + start_of_object_name];
        }
        char *folder_path = calloc((size_t) end_of_object_name + 1, sizeof(char));
        if (folder_path == NULL) {
            perror("can not allocate memory for folder path!");
            exit(1);
        }
        for (int k = 0; k < start_of_object_name - 1; ++k) {
            folder_path[k] = path[k];
        }
        string_pair *nameVsFolder = new_string_pair(object_name, folder_path);
        return nameVsFolder;
    }
    perror("invalid aio aio_context name error!");
    exit(1);
}

string_list *read_file_and_collect_to_string_list(const char *path) {
    string_list *strings = new_string_list();
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
        //Put string in list:
        add_in_string_list(strings, line);
    }
    fclose(file);
    return strings;
}