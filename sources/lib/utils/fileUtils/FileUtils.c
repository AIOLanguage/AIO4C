#include "../../../../headers/lib/utils/stringUtils/string_utils.h"
#include "../../../../headers/lang/object/AIOObject.h"
#include <malloc.h>
#include <mem.h>
#include <stdio.h>

void mergeNewFolderPath(char *folderPath, char *nextObjectName, char **absoluteNextObjectPath) {
    //Not supported:
    //While easy make concat_string_to_string =)
    char **paths = calloc(2, sizeof(char *));
    paths[0] = folderPath;
    paths[1] = nextObjectName;
//    join_to_string_without_spaces(paths, absoluteNextObjectPath);
}


//Passed JUnitTest!
StringPair *extractNameAndFolderPathFromPath(char *path) {
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
        StringPair *nameVsFolder = calloc(1, sizeof(StringPair));
        nameVsFolder->first = objectName;
        nameVsFolder->second = folderPath;
        return nameVsFolder;
    }
    perror("invalid aio object name error!");
}