#include "../../../../headers/lib/utils/stringUtils/StringUtils.h"
#include <malloc.h>

void mergeNewFolderPath(char *folderPath, char *nextObjectName, char **absoluteNextObjectPath) {
    //Not supported:
    //While easy make concat =)
    char **paths = calloc(2, sizeof(char *));
    paths[0] = folderPath;
    paths[1] = nextObjectName;
    joinToStringWithoutSpaces(paths, absoluteNextObjectPath);
}