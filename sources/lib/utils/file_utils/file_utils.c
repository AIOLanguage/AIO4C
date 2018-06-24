#include "../../../../headers/lang/object/aio_object.h"
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
            perror("can not allocate memory for object name!");
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
    perror("invalid aio object name error!");
    exit(1);
}