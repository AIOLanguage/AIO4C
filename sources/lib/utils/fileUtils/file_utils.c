#include "../../../../headers/lib/utils/stringUtils/string_utils.h"
#include "../../../../headers/lang/object/aio_object.h"
#include <malloc.h>
#include <mem.h>
#include <stdio.h>

void merge_new_folder_path(char *folder_path, char *next_object_name, char **absolute_next_object_path) {
    //Not supported:
    //While easy make concat_string_to_string =)
    char **paths = calloc(2, sizeof(char *));
    paths[0] = folder_path;
    paths[1] = next_object_name;
//    join_to_string_without_spaces(paths, absolute_next_object_path);
}


//Passed JUnitTest!
string_pair *extract_name_and_folder_path_from_path(char *path) {
    //*.aio:
    int pathLength = strlen(path);
    if (pathLength > 4) {
        //without last .aio:
        int startOfObjectName = 0;
        char pointer;
        int endOfObjectName = pathLength - 5;
        for (int i = endOfObjectName; i >= 0; --i) {
            pointer = path[i];
            if (pointer == '/') {
                break;
            }
            startOfObjectName = i;
        }
        unsigned size = (unsigned int) (endOfObjectName - startOfObjectName + 1);
        char *objectName = calloc(size + 1, sizeof(char));
        if (objectName == NULL) {
            perror("can not calloc memory for object name!");
        }
        for (int j = 0; j < size; ++j) {
            objectName[j] = path[j + startOfObjectName];
        }
        char *folderPath = calloc((size_t) endOfObjectName + 1, sizeof(char));
        if (folderPath == NULL) {
            perror("can not allocate memory for folder path!");
        }
        for (int k = 0; k < startOfObjectName - 1; ++k) {
            folderPath[k] = path[k];
        }
        string_pair *nameVsFolder = calloc(1, sizeof(string_pair));
        nameVsFolder->first = objectName;
        nameVsFolder->second = folderPath;
        return nameVsFolder;
    }
    perror("invalid aio object name error!");
}